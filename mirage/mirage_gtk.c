#include <stdlib.h>
#include <gtk/gtk.h>
#include "mirage_gtk.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

GdkColor color, color2;

int main(int argc,char **argv)
{ 
  GtkWidget *window, *pixmap;
  GtkWidget *fixed, *pEntry;
  GtkWidget *button, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9, *button10, *button11;
  GtkWidget *colorbutton, *colorbutton2;
  GtkWidget *brush, *line, *rect, *frect, *circle, *fcircle, *poly, *fpoly, *degl, *degc;

  gtk_init(&argc, &argv);

  color.red = 0;      color.green = 0;      color.blue = 0;
  color2.red = 65535; color2.green = 65535; color2.blue = 65535;
  Write_tool(0, 4,0,0,0,65535,65535,65535);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 160, 720);
  gtk_window_set_title(GTK_WINDOW(window), "Toolbox");

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);

  button =  gtk_button_new();
  gtk_widget_set_size_request(button, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button, 0, 0);
  brush = gtk_image_new_from_file("brush.png");
  gtk_button_set_image(button, brush);

  button2 = gtk_button_new();
  gtk_widget_set_size_request(button2, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button2, 80, 0);
  line = gtk_image_new_from_file("line.gif");
  gtk_button_set_image(button2, line);

  button3 = gtk_button_new();
  gtk_widget_set_size_request(button3, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button3, 0, 80);
  rect = gtk_image_new_from_file("rectangle.gif");
  gtk_button_set_image(button3, rect);

  button4 = gtk_button_new();
  gtk_widget_set_size_request(button4, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button4, 80, 80);
  frect = gtk_image_new_from_file("frect.gif");
  gtk_button_set_image(button4, frect);

  button5 = gtk_button_new();
  gtk_widget_set_size_request(button5, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button5, 0, 160);
  circle = gtk_image_new_from_file("circle.gif");
  gtk_button_set_image(button5, circle);

  button6 = gtk_button_new();
  gtk_widget_set_size_request(button6, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button6, 80, 160);
  fcircle = gtk_image_new_from_file("fcircle.jpg");
  gtk_button_set_image(button6, fcircle);

  button7 = gtk_button_new();
  gtk_widget_set_size_request(button7, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button7, 0, 240);
  poly = gtk_image_new_from_file("poly.png");
  gtk_button_set_image(button7, poly);

  button8 = gtk_button_new();
  gtk_widget_set_size_request(button8, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button8, 80, 240);
  degl = gtk_image_new_from_file("degl.png");
  gtk_button_set_image(button8, degl);

  button9 = gtk_button_new();
  gtk_widget_set_size_request(button9, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button9, 0, 320);
  degc = gtk_image_new_from_file("degc.png");
  gtk_button_set_image(button9, degc);

  button10 = gtk_button_new();
  gtk_widget_set_size_request(button10, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button10, 80, 320);
  fpoly = gtk_image_new_from_file("fpoly.png");
  gtk_button_set_image(button10, fpoly);

  button11 = gtk_button_new();
  gtk_widget_set_size_request(button11, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), button11, 0, 400);
  fpoly = gtk_image_new_from_file("pot.png");
  gtk_button_set_image(button11, fpoly);

  colorbutton = gtk_color_button_new_with_color(&color);
  gtk_widget_set_size_request(colorbutton, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), colorbutton, 0, 480);

  colorbutton2 = gtk_color_button_new_with_color(&color2);
  gtk_widget_set_size_request(colorbutton2, 80, 80);
  gtk_fixed_put(GTK_FIXED(fixed), colorbutton2, 80, 480);

  pEntry = gtk_entry_new_with_max_length(2);
  gtk_widget_set_size_request(pEntry, 35, 20);
  gtk_fixed_put(GTK_FIXED(fixed), pEntry, 60, 600);

  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(click_button), NULL);
  g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(click_button2), NULL);
  g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(click_button3), NULL);
  g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(click_button4), NULL);
  g_signal_connect(G_OBJECT(button5), "clicked", G_CALLBACK(click_button5), NULL);
  g_signal_connect(G_OBJECT(button6), "clicked", G_CALLBACK(click_button6), NULL);
  g_signal_connect(G_OBJECT(button7), "clicked", G_CALLBACK(click_button7), NULL);
  g_signal_connect(G_OBJECT(button8), "clicked", G_CALLBACK(click_button8), NULL);
  g_signal_connect(G_OBJECT(button9), "clicked", G_CALLBACK(click_button9), NULL);
  g_signal_connect(G_OBJECT(button10), "clicked", G_CALLBACK(click_button10), NULL);
  g_signal_connect(G_OBJECT(button11), "clicked", G_CALLBACK(click_button11), NULL);

   g_signal_connect(G_OBJECT(pEntry), "activate", G_CALLBACK(on_activate_entry), NULL);

  g_signal_connect(G_OBJECT(button), "enter", G_CALLBACK(enter_button), NULL);
  g_signal_connect(G_OBJECT(button2), "enter", G_CALLBACK(enter_button), NULL);
  g_signal_connect(G_OBJECT(button3), "enter", G_CALLBACK(enter_button), NULL);
  g_signal_connect(G_OBJECT(button4), "enter", G_CALLBACK(enter_button), NULL);
  g_signal_connect(G_OBJECT(button5), "enter", G_CALLBACK(enter_button), NULL);
  g_signal_connect(G_OBJECT(button6), "enter", G_CALLBACK(enter_button), NULL);
  g_signal_connect(G_OBJECT(button7), "enter", G_CALLBACK(enter_button), NULL);
  g_signal_connect(G_OBJECT(button8), "enter", G_CALLBACK(enter_button), NULL);
  g_signal_connect(G_OBJECT(button9), "enter", G_CALLBACK(enter_button), NULL);
  g_signal_connect(G_OBJECT(button10), "enter", G_CALLBACK(enter_button), NULL);
  g_signal_connect(G_OBJECT(button11), "enter", G_CALLBACK(enter_button), NULL);

  g_signal_connect(G_OBJECT(colorbutton), "color-set", G_CALLBACK(setcolor), NULL);
  g_signal_connect(G_OBJECT(colorbutton2), "color-set", G_CALLBACK(setcolor2), NULL);

  g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}

void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
    /* Arret de la boucle evenementielle */
    gtk_main_quit();
    (void)pWidget;
    (void)pData;
}

void Read_tool(int *choice, int *num, 
                int *r1, int *g1, int *b1,
                int *r2, int *g2, int *b2)
{
  int fd;
  static const char filename[] = "tmp/tool";
  fd = open(filename,O_RDONLY);
  char line[128];
  read(fd, line, 128);

  *choice = atoi(strtok (line," "));
  *num = atoi(strtok (NULL," "));

  *r1 = atoi(strtok (NULL," "));
  *g1 = atoi(strtok (NULL," "));
  *b1 = atoi(strtok (NULL," "));

  *r2 = atoi(strtok (NULL," "));
  *g2 = atoi(strtok (NULL," "));
  *b2 = atoi(strtok (NULL," "));

  close(fd);
}

void Write_tool(int choice, int num, 
                int r1, int g1, int b1,
                int r2, int g2, int b2)
{
  char filename[128];
  sprintf(filename,"echo \"%d %d %d %d %d %d %d %d\" > tmp/tool", choice, num,r1,g1,b1,r2,g2,b2);
  system(filename);
}

void setcolor(GtkWidget *pWidget, gpointer pData)
{
  gtk_color_button_get_color (pWidget,&color);
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  r1 = (color.red*255)/65535;
  g1 = (color.green*255)/65535;
  b1 = (color.blue*255)/65535;
  r2 = (color2.red*255)/65535;
  g2 = (color2.green*255)/65535;
  b2 = (color2.blue*255)/65535;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void setcolor2(GtkWidget *pWidget, gpointer pData)
{
  gtk_color_button_get_color (pWidget,&color2);
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  r1 = (color.red*255)/65535;
  g1 = (color.green*255)/65535;
  b1 = (color.blue*255)/65535;
  r2 = (color2.red*255)/65535;
  g2 = (color2.green*255)/65535;
  b2 = (color2.blue*255)/65535;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void on_activate_entry(GtkWidget *pEntry, gpointer data)
{
  const gchar *sText;
  sText = gtk_entry_get_text(GTK_ENTRY(pEntry));
  //gtk_label_set_text(GTK_LABEL((GtkWidget*)data), sText);
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  num=atoi(sText);
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=0;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button2(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=1;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button3(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=2;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button4(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=3;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button5(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=4;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button6(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=5;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button7(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=6;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button8(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=7;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button9(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=8;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button10(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=9;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

void click_button11(GtkWidget *pWidget, gpointer pData)
{
  int r1,g1,b1,r2,g2,b2,choice,num;
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2);
  choice=10;
  Write_tool(choice, num, r1, g1, b1, r2,g2, b2);
}

// Change couleur kan la souris pass sur le bouton
void enter_button(GtkWidget *pWidget, gpointer pData)
{
  GdkColor color;
  color.red = 50000;
  color.green = 50000;
  color.blue = 50000;
  gtk_widget_modify_bg(pWidget, GTK_STATE_PRELIGHT, &color);
  (void)pWidget;
  (void)pData;
}