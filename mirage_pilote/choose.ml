                                                                                                                
(* Dimensions d'une image *)
let get_dims img =
  ((Sdlvideo.surface_info img).Sdlvideo.w, (Sdlvideo.surface_info img).Sdlvideo.h)


let sdl_init () =
  begin
    Sdl.init [`EVERYTHING];
    Sdlevent.enable_events Sdlevent.all_events_mask;
  end


let rec wait_key () =
  let e = Sdlevent.wait_event () in
    match e with
    Sdlevent.KEYDOWN _ -> ()
      | _ -> wait_key ()

let show img dst =
  let d = Sdlvideo.display_format img in
    Sdlvideo.blit_surface d dst ();
    Sdlvideo.flip dst


let compare (a, b) = if (a = b) then
true
  else false ;;

let colorselect = (42,21,42);;


let color img2 i j =
   if ((((i+j)/2)*2)==(i+j)) then (3,1,1)                                                                           
   else (255,252,252) 

let modifPiX img2 x y =
  Sdlvideo.put_pixel_color img2 x y (color img2 x y) ;;


let plusfonce (r,g,b) = (r/1,g/1,b/1)


let rec fonce img1 img2 =
  let (w, h) = get_dims img1
  in
    for j = 0 to (w - 2) do
      for i = 0 to (h - 2) do
          Sdlvideo.put_pixel_color img2 i j (plusfonce(Sdlvideo.get_pixel_color
                                               img1 (i) (j) ))
      done
    done 

(*let rec select2 img1 img2 =
  let (w, h) = get_dims img1 
  in
  for j = 0 to (w - 2) do
    for i = 0 to (h - 2) do
      if ((Sdlvideo.get_pixel_color img2 i j)==colorselect) then modifpix2 img2 i j;
	        
	  if ((((i+j)/2)*2)==(i+j)) then Sdlvideo.put_pixel_color img2 i j (1,2,3)
	  else Sdlvideo.put_pixel_color img2 i j (253,254,255)
	 ()
    done
  done*)

let rec select img2 j i =
  let (w, h) = get_dims img2
  in
  if (j<(w-1)) then ( 
    if (Sdlvideo.get_pixel_color img2 j i)==(color img2 i j) then Sdlvideo.put_pixel_color img2 j i (255,0,0);
     select img2 (j+1) i)
  else 
    (if i<(h-1) then
	select img2 1 (i+1))
  

let rec choose1 im1 im2 i j coul=
  let (w, h) = get_dims im1
  in               
  (*if (Sdlvideo.get_pixel_color im1 i j)==(0,0,255) then*)
    ( (begin (modifPiX im2 i j)
       end);
      if (compare ((Sdlvideo.get_pixel_color im1 i j),
		   (Sdlvideo.get_pixel_color im1 i (j+1) )))&&(j<(h-2))&&((Sdlvideo.get_pixel_color im2 (i) (j+1))<>(color im2 i (j+1))) then
	
	choose1 im1 im2 i (j+1) coul;
      
      if  (compare ((Sdlvideo.get_pixel_color im1 i j),
		    (Sdlvideo.get_pixel_color im1 (i-1) j )))&&(i>(0  ))&&((Sdlvideo.get_pixel_color im2 (i-1) (j))<>(color im2 (i-1) j)) then
	
	choose1 im1 im2 (i-1) (j) coul;
      
      
      if (compare ((Sdlvideo.get_pixel_color im1 i j),                                                                                         
		   (Sdlvideo.get_pixel_color im1 i (j-1) )))&&(j>(0 ))&&((Sdlvideo.get_pixel_color im2 (i) (j-1))<>(color im2 i (j-1))) then 
	
	choose1 im1 im2 i (j-1) coul;                                                                                                                    
      
      if  (compare ((Sdlvideo.get_pixel_color im1 i j),                                                                                         
		    (Sdlvideo.get_pixel_color im1 (i+1) j )))&&(i<(w-2))&&((Sdlvideo.get_pixel_color im2 (i+1) (j))<>(color im2 (i+1) j)) then           
	
	choose1 im1 im2 (i+1) (j) coul                                                                                                              
    )



let rec choose im1 im2 i j = choose1 im1 im2 i j (Sdlvideo.get_pixel_color im1 i j)







let main ()  =
begin
  let img = Sdlloader.load_image Sys.argv.(1) in
  let (h,w) = get_dims img in
  let (x,y) = (int_of_string Sys.argv.(2),int_of_string Sys.argv.(3))in
  let img2 = Sdlvideo.create_RGB_surface_format img [] w h in
fonce img img2; (*obliger de laisser*)

  let display = Sdlvideo.set_video_mode w h [`DOUBLEBUF] in
      show img2 display;
      wait_key ();
      choose img img2 (x) (y);
      show (img2) display;
      wait_key ();
      select img2 1 1;
      show img2 display;
      wait_key ();


      
end

let _ = main ()
