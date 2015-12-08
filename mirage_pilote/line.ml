(* standardZ.ml : supprime le bruit sur une image. *)
(* Cree par Quentin Mignot pour le projet MapViewer (2011) *)
(* Copyright : Copie, modification et distribution autorisees *)


(* Dimensions d'une image *)
let get_dims img =
  ((Sdlvideo.surface_info img).Sdlvideo.w, (Sdlvideo.surface_info img).Sdlvideo.h)
 
(* init de SDL *)
let sdl_init () =
  begin
    Sdl.init [`EVERYTHING];
    Sdlevent.enable_events Sdlevent.all_events_mask;
  end
 
(* attendre une touche ... *)
let rec wait_key () =
  let e = Sdlevent.wait_event () in
    match e with
    Sdlevent.KEYDOWN _ -> ()
      | _ -> wait_key ()
 
(*
  show img dst
  affiche la surface img sur la surface de destination dst (normalement l'écran)
*)
let show img dst =
  let d = Sdlvideo.display_format img in
    Sdlvideo.blit_surface d dst ();
    Sdlvideo.flip dst

let askTol s = (* return a percent between 0 an 100 called tolerance. tolerance will decide if two pixels have the same color or not *)
  (*let t = -2 in
while t > -2 && t < 101
do
print_newline ();
print_string(s);
t = int_of_string(read_line());
done;
t;;*)
int_of_string(Sys.argv.(2));;

let rec test_tol tol (r, g, b) = function
  | [] -> (-1, -1, -1)
  | (r2, g2, b2)::l when ((r < r2 + tol && r > r2 - tol) && (g < g2 + tol && g > g2 - tol) && (b < b2 + tol && b > b2 - tol)) -> (r2, g2, b2)
  | e::l -> test_tol tol (r, g, b) l;;



let print_triplet (r, g, b) = 
print_string "(";
print_int r;
print_string ",";
print_int g;
print_string ",";
print_int b;
print_string ") ";;

let rec print_list = function
| [] -> print_string "\n"
| e::l -> begin print_triplet e; print_list l end;;



let rec pix_in_list_with_tol tol n (r, g, b) l =
if n <= tol then
if ((test_tol n (r, g, b) l) = (-1, -1, -1)) then (pix_in_list_with_tol tol (n+1) (r, g, b) l) else (test_tol n (r, g, b) l)
else (-1, -1, -1);;

let abs n = if n < 0 then -n else n;;


let get_diff (r1, g1, b1) (r2, g2, b2) = (* return the difference percent beween the two pixels *)
  let dr = abs (r1 - r2) and dg = abs (g1 - g2) and db = abs (b1 - b2) in (* dr dg and db are the deltas betweens the differents color's channels *)
  let p = int_of_float((33. /. 255.) *. float_of_int (dr + dg + db) ) in
p (* p is the finally differnce percent *);;


let standardZ pic =
  let tol = askTol "Please enter a percent tolerence [0, 100] or -1 for default : " in (* tol : tolerance *)
  let color_list = ref [] in (* cantain the color list of the image to be sure a color has been already encoutered or not *)
  let (w, h) = (get_dims pic) in (* w is the number of columns of pic, h is the number of lines *)
  let ext = pic in
  let color = ref (-1, -1, -1) in
for y = 0 to h - 1 do
for x = 0 to w - 1 do
(* print_list !color_list; *)
 color := pix_in_list_with_tol tol 0 (Sdlvideo.get_pixel_color pic x y) !color_list;
if ((!color) <> (-1, -1, -1)) (* (-1, -1, -1) : Le pixel n'a pas ete vu *)
  then (* pixel's color we are seeing has been already seen*)
    begin
      Sdlvideo.put_pixel_color ext x y (!color)
    end 
  else
    begin
      color_list := (Sdlvideo.get_pixel_color pic x y)::(!color_list)
    end
done;
done;
for y = 1 to h - 2 do
for x = 1 to w - 2 do
	if
	 (
		(
	(Sdlvideo.get_pixel_color ext (x - 1) y) = (Sdlvideo.get_pixel_color ext x (y-1))
		) &&
		(
	(Sdlvideo.get_pixel_color ext (x - 1) y) = (Sdlvideo.get_pixel_color ext x (y + 1))
		) 
      	)
	then Sdlvideo.put_pixel_color ext x y (Sdlvideo.get_pixel_color pic (x-1) y);
	if
	(
		(
	(Sdlvideo.get_pixel_color ext  (x + 1) y) = (Sdlvideo.get_pixel_color ext x (y - 1))
		) &&
		(
	(Sdlvideo.get_pixel_color ext  (x + 1) y) = (Sdlvideo.get_pixel_color ext x (y + 1))
		)
	)

 	then
	Sdlvideo.put_pixel_color ext x y (Sdlvideo.get_pixel_color pic (x+1) (y));

	if
	 (
		(
	(Sdlvideo.get_pixel_color ext (x ) (y-1)) = (Sdlvideo.get_pixel_color ext  (x-1) y)
		) &&
		(
	(Sdlvideo.get_pixel_color ext (x ) (y-1)) = (Sdlvideo.get_pixel_color ext  (x + 1) y)
		) 
      	)
	then Sdlvideo.put_pixel_color ext x y (Sdlvideo.get_pixel_color pic (x) (y-1));

	if
	 (
		(
	(Sdlvideo.get_pixel_color ext (x) (y+1)) = (Sdlvideo.get_pixel_color ext  (x -1) y)
		) &&
		(
	(Sdlvideo.get_pixel_color ext (x) (y+1)) = (Sdlvideo.get_pixel_color ext  (x + 1) y)
		) 
      	)
	then Sdlvideo.put_pixel_color ext x y (Sdlvideo.get_pixel_color pic x (y+1) );

done;
done;
ext;;



let main () =
  begin
    (* Nous voulons 1 argument *)
    if Array.length (Sys.argv) < 3 then
      failwith "Il manque le nom du fichier ou la tolérance !";
    (* Initialisation de SDL *)
    sdl_init ();
    (* Chargement d'une image *)
    let img = Sdlloader.load_image Sys.argv.(1) in
Sdlvideo.put_pixel_color img 10 10 (200,20,30);
    (* On récupère les dimensions *)
    let (w,h) = get_dims img in
    (* On crée la surface d'affichage en doublebuffering *)
    let display = Sdlvideo.set_video_mode w h [`DOUBLEBUF] in
      (* on affiche l'image *)
      show img display;     
      (* on attend une touche *)
      wait_key ();
      let img2 = standardZ img in
      show img2 display;
      wait_key (); 
	if (Sdlvideo.get_pixel_color img2 10 10) = (200, 20, 30) then print_string "epic fail";
      (* on quitte *)
      exit 0
  end


let _ = main ();;

 
