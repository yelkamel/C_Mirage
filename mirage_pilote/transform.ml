
let get_dims img =
  ((Sdlvideo.surface_info img).Sdlvideo.w, (Sdlvideo.surface_info img).Sdlvideo.h)

let sdl_init () =
  begin
    Sdl.init [`EVERYTHING];
    Sdlevent.enable_events Sdlevent.all_events_mask;
  end

let rec wait_mouse () =
  let e = Sdlevent.wait_event () in
    match e with
	Sdlevent.MOUSEBUTTONDOWN _-> ()
      | _ -> wait_mouse ()

let rec wait_key () =
  let e = Sdlevent.wait_event () in
    match e with	
	  Sdlevent.KEYDOWN _ -> ()
      | _ -> wait_key ()

let show img dst =
  let d = Sdlvideo.display_format img in
    Sdlvideo.blit_surface d dst ();
    Sdlvideo.flip dst

let rec imgtest img = let (h, w) = get_dims img  in
    for j = 0 to (w - 2) do
      for i = 0 to (h - 2) do
         Sdlvideo.put_pixel_color img i j (42,42,42)
      done
    done
let limcoul (r,g,b)= let lc x = if x > 255 then 255 else ( if x < 0 then 0 else x ) in(lc r,lc g,lc b);;
let violet (r,g,b)=limcoul (b*2,g,r/2)
let vert (r,g,b)= (g,r,b)
let noir (r,g,b)= (g,g,g)
let bleu (r,g,b)=(b,g,r)
let blanc (r,g,b)= limcoul(r,r,r)
let tourne (r,g,b)= (r,g,b)
let tourne2 (r,g,b)= (r,g,b)
let tourne3 (r,g,b)= (g,r,b)
let p x = if (x<0) then (0-x) else x
let z0 x = if x=0 then 1 else x 
let compare (a, b) = if (a = b) then true  else false ;;  
let plusfonce (r,g,b) = ((r/2)+(r/3),(g/2)+(g/3),(b/2)+(b/3))
let plusclaire (r,g,b) = limcoul(r+(r/4),g+(g/4),b+(b/4))
let moinslumineux (r,g,b) = ((r/2)+((g+b)/4),(g/2)+((r+b)/4),(b/2)+((r+g)/4))
let inverse (r,g,b) = ((255-r), (255-g), (255-b))
let pluslumineux (r,g,b) = limcoul( ((r*2)-((g+b)/4)), ((g*2)-((r+b)/4)), ((b*2)-((r+g)/4)) )
let col (x,y)= (255,0,0)
let decontrast (r,g,b)= let decon x = x+((128-x)/8) in (decon r,decon g,decon b)  
let contrast (r,g,b)= let con x = x-((128-x)/8) in limcoul(con r,con g,con b)
let sun_effect (r,g,b) x y h w= let deg p x y = ((((h/2+w/2+h/4+w/4)-x-y)/8)+(p/2)+(p/4)+(p/6))  in limcoul(deg r x y,deg g x y,deg b x y) 
let flou (r,g,b) (rr,gg,bb) = let fl x xx = if x<xx then ( xx+((x-xx)/2) ) else ( xx+((x-xx)/2) ) in (fl r rr,fl g gg,fl b bb)
let mirroir (r,g,b) x y h w=let tt p x y= p  in (tt r x y,tt g x y,tt b x y)
let bordflou (r,g,b) (rr,gg,bb) x y h w =limcoul( (r+z0 ((rr* (p (x-(h/2)))) /100000)),
					   (g+z0 (gg*((p (x-(h/2))))/100000)), (b+z0 ((bb*(p (x-(h/2))))/100000)) ) 

let laisserouge (r,g,b) = if (r>50)&&(r>(g-1))&&((g-b)<=20) then  (r,g,b) else moinslumineux (r,g,b);;
let vertisation (r,g,b) x = if ((r>80)&&(r>(g+40))&&((g-b)<=20))||((r>100)&&(g>150)&&((r-b)>=0)&&(g-b<30)) then
    
if ((x/2)*2)==x then                  vert (r,g,b)             else tourne2 (r,g,b)
else  (r,g,b);;


let bleuisation (r,g,b) x = if ((r>80)&&(r>(g+40))&&((g-b)<=20))||((r>100)&&(g>150)&&((r-b)>=0)&&(g-b<30)) then

if ((x/2)*2)==x then                  bleu (r,g,b)             else tourne2 (r,g,b)
  else  (r,g,b);;

let violetisation (r,g,b) x = if ((r>80)&&(r>(g+40))&&((g-b)<=20))||((r>100)&&(g>150)&&((r-b)>=0)&&(g-b<30)) then

if ((x/2)*2)==x then                  violet (r,g,b)             else tourne2 (r,g,b)
  else  (r,g,b);;

let blancisation (r,g,b) x = if ((r>80)&&(r>(g+40))&&((g-b)<=20))||((r>100)&&(g>150)&&((r-b)>=0)&&(g-b<30)) then

if ((x/2)*2)==x then                  blanc (r,g,b)             else tourne2 (r,g,b)
  else  (r,g,b);;

let noirisation (r,g,b) x = if ((r>80)&&(r>(g+40))&&((g-b)<=20))||((r>100)&&(g>150)&&((r-b)>=0)&&(g-b<30)) then

if ((x/2)*2)==x then                  noir (r,g,b)             else tourne2 (r,g,b)
  else  (r,g,b);;


(*let rec modif img1 img2 img3 i j= 
  let (h, w) = get_dims img1
  in if (i>=1)&&(i<=w-3)&&(j>=1)&&(j<=h-3) then 
      if ( ((Sdlvideo.get_pixel_color img3 (i) (j))<>(42,42,42)) )then
      
	(Sdlvideo.put_pixel_color img3 (i) (j) (200,100,100));
	  Sdlvideo.put_pixel_color img2 i j (inverse(Sdlvideo.get_pixel_color img1 (i) (j) ));
	    modif img1 img2 img3 (i+1) j;
	  modif img1 img2 img3 (i) (j+1);;*)




let rec change img1 img2 n c x =
  let (h, w) = get_dims img1 in

    for i= 0 to h do
      for j= 0  to w do
	match n with
	 (*Couleurs negatives*) |"inverse" ->  Sdlvideo.put_pixel_color img2 i j (inverse(Sdlvideo.get_pixel_color
                                       img1 (i) (j) ))

	 (*Moins lumineux*)  |"sombre"->  Sdlvideo.put_pixel_color img2 i j (moinslumineux(Sdlvideo.get_pixel_color
                                       img1 (i) (j) ))
 
	 (*Plus lumineux*)  |"lumineux"-> Sdlvideo.put_pixel_color img2 i j (pluslumineux(Sdlvideo.get_pixel_color                  
                             img1 (i) (j) ))

	 (*Plus claire*)  |"claire"-> Sdlvideo.put_pixel_color img2 i j (plusclaire(Sdlvideo.get_pixel_color
                             img1 (i) (j) ))
	  
	 (*Plus fonce*)  |"fonce"-> Sdlvideo.put_pixel_color img2 i j (plusfonce(Sdlvideo.get_pixel_color
                             img1 (i) (j) ))
	  
	 (*Moins de contrastes*)  |"decontraste"-> Sdlvideo.put_pixel_color img2 (i) (j) (decontrast(Sdlvideo.get_pixel_color
                             img1 (i) (j) ))

	 (*Plus de contrastes**)  |"contraste"-> Sdlvideo.put_pixel_color img2 (i) (j) (contrast(Sdlvideo.get_pixel_color
                             img1 (i) (j) ))

	 (*Ensoleillement*)  |"ensoleillement"-> Sdlvideo.put_pixel_color img2 (i) (j) (sun_effect (Sdlvideo.get_pixel_color
                             img1 (i) (j) ) ( i ) ( j ) h w )

	 (*Floutage*) |"flou"-> Sdlvideo.put_pixel_color img2 (i+1) (j+1) (flou (Sdlvideo.get_pixel_color img1 i j)
									(Sdlvideo.get_pixel_color img1 (i+1) (j+1)))


	 (*Mirroir horizontale*)  |"mirroir"->  Sdlvideo.put_pixel_color img2 (h-i) (j) (mirroir (Sdlvideo.get_pixel_color
                                       img1 (i) (j) ) i j h w);
	 
	   (*just rouge*) |"laisse"->  Sdlvideo.put_pixel_color img2 i j (laisserouge(Sdlvideo.get_pixel_color
                                       img1 (i) (j) ))
	
	  | "rouge"-> ( match c with 
	      |  "vert" -> Sdlvideo.put_pixel_color img2 i j (vertisation(Sdlvideo.get_pixel_color
                                       img1 (i) (j) )x)
	      
	  (*|13->*) | "bleu" ->  Sdlvideo.put_pixel_color img2 i j (bleuisation(Sdlvideo.get_pixel_color
                                       img1 (i) (j) )x)
	      
	  (*|14-*) | "violet" ->  Sdlvideo.put_pixel_color img2 i j (violetisation(Sdlvideo.get_pixel_color
                                       img1 (i) (j) )x)

	      | "noir" ->  Sdlvideo.put_pixel_color img2 i j (noirisation(Sdlvideo.get_pixel_color
                                       img1 (i) (j) )x)
 
	  (*|15->*) | _ -> Sdlvideo.put_pixel_color img2 i j (blancisation(Sdlvideo.get_pixel_color
									     img1 (i) (j) )x)
	      )
	
          | "vert"-> ( match c with
              

          (*|13->*) | "bleu" ->  Sdlvideo.put_pixel_color img2 i j (bleuisation (tourne3(bleuisation( tourne3(Sdlvideo.get_pixel_color img1 (i) (j)) )x)) x)

          (*|14-*) | "violet" ->  Sdlvideo.put_pixel_color img2 i j (violetisation(tourne3(Sdlvideo.get_pixel_color
                                       img1 (i) (j) ))x)

          (*|15->*) | _ -> Sdlvideo.put_pixel_color img2 i j (blancisation(Sdlvideo.get_pixel_color
                                                                             img1 (i) (j) )x)
          )



	  


  
 (*(*change coul*) |12->  if ((x/2)*2)==x then Sdlvideo.put_pixel_color img2 i j (vertisation(Sdlvideo.get_pixel_color
                                       img1 (i) (j) ) x)
   else Sdlvideo.put_pixel_color img2 i j (vertisation(tourne(Sdlvideo.get_pixel_color
                                       img1 (i) (j) ) )x)*)

  (*|12->(  match x with 
      |0 -> Sdlvideo.put_pixel_color img2 i j (vertisation((Sdlvideo.get_pixel_color
                                       img1 (i) (j) )) x)
      |1-> Sdlvideo.put_pixel_color img2 i j (vertisation(tourne(Sdlvideo.get_pixel_color
                                       img1 (i) (j) )) x)
      |2-> Sdlvideo.put_pixel_color img2 i j (vertisation(tourne2(Sdlvideo.get_pixel_color
                                       img1 (i) (j) )) (x))
      |x-> if ((x/2)*2)==x then Sdlvideo.put_pixel_color img2 i j (vertisation(tourne(Sdlvideo.get_pixel_color
                                       img1 (i) (j) ) )x)
	else Sdlvideo.put_pixel_color img2 i j (vertisation(tourne2(Sdlvideo.get_pixel_color
                                       img1 (i) (j) ) )x)) *)
  
    

(*Contours*) |"contour"-> Sdlvideo.put_pixel_color img2 (i+1) (j+1) (bordflou (Sdlvideo.get_pixel_color img1 i j) 
									  (Sdlvideo.get_pixel_color img1 (i+1) (j+1)) i j w h)
 



	  (*Sinon rien*)|_->()
      done
    done   

let argu tab = if (tab > 4) then Sys.argv.(4) else "rien"
(*let argu2 tab = if (tab = 7) then (int_of_string(Array.length Sys.argv),(int_of_string ( Array.length Sys.argv))-1,(int_of_string (Array.length Sys.argv))-2,(int_of_string (Array.length Sys.argv))-3) else (0,0,0,0)*) 

let rec key n c img img2 img3 display x nom=
  let e = Sdlevent.wait_event () in
    match e with
     (*Clique sourie -> execution programme*) | Sdlevent.MOUSEBUTTONDOWN _ -> change img img2 n c x (*modif img img2 img3 50 50 *);(show img2 display);(key n c img2 img2 img3 display (x) nom);Sdlvideo.save_BMP img2 nom
     (*Appuier une touche -> Quit le programme*) |  Sdlevent.KEYDOWN _-> ()
     (*Boucle infinie -> Attend le prochain evenement*) | _ -> (key n c img img2 img3 display x nom)


let main ()  =
begin
 (*Chargement image initiale*) let img = Sdlloader.load_image Sys.argv.(1) in
			     let n = (*int_of_string*) Sys.argv.(3) in
			     let nom = (*int_of_string*) Sys.argv.(2) in
 
let tab =(Array.length Sys.argv)in 
(* let c = argu tab in *)
 let c = argu tab in

  (*Dimentions image*)let (w,h) = get_dims img in
  let img2 = img in
  (*let img3 = img in*)
  let display = Sdlvideo.set_video_mode w h [`DOUBLEBUF] in
  (*imgtest img3;*)
  (*Affichage image initiale*)show (img) display;
  (*Attend un commande*) key n c img img2 img2 display 0 nom;        
end

let _ = main ()
