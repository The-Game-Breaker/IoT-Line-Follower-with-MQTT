//Ball caster.
//Parametric.
//Oktay Gülmez, 24/2/2016.
//GNU_GPL_V3


//Parameters:
//Diameter of the marble in mm.
ball_diameter=24;
//Desired height: (Minimum=ball_diameter+2mm.)
caster_height=33;
//Distance of the mounting holes center in mm.
mountingHoles_width=35;
//Diameter of the mounting screws. 2 for M2, 3 for M3.
mountingScrew_dia=3;
//Nozzle diameter of your printer's in mm.
nozzle_dia=0.4;
//Diameter of the Washer for reducing friction in mm.
washer_dia=20;
//Thickness of the Washer for reducing friction in mm.
washer_thickness=1.9;

$fn=60;
difference(){
    union(){
 //Body: 
       translate([0,0,0]) cylinder(h=ball_diameter/2-2, r=ball_diameter/2+4*nozzle_dia); 
       translate([0,0,ball_diameter/2-2]) sphere(r=ball_diameter/2+4*nozzle_dia);  
 //Mounting:       
        linear_extrude(height = 3, convexity = 10) hull() {
   translate([-mountingHoles_width/2,0,0])circle(5);
   translate([0,0,0]) circle(ball_diameter/2+4*nozzle_dia);
        }
        linear_extrude(height = 3, convexity = 10) hull() {
   translate([0,0,0])circle(ball_diameter/2+4*nozzle_dia);
   translate([mountingHoles_width/2,0,0]) circle(5);
        }
 //Spacer:      
        linear_extrude(height = caster_height-ball_diameter, convexity = 10, $fn=60) hull() {
   translate([-mountingHoles_width/2,ball_diameter+5,0])circle(5);
   translate([0,ball_diameter+5,0]) circle(ball_diameter/2+4*nozzle_dia);
        }
        linear_extrude(height = caster_height-ball_diameter, convexity = 10, $fn=60) hull() {
   translate([0,ball_diameter+5,0])circle(ball_diameter/2+4*nozzle_dia);
   translate([mountingHoles_width/2,ball_diameter+5,0]) circle(5);
        }
        
    }
    
//Top cut:   
    translate([-ball_diameter/2-2,-ball_diameter/2-2,ball_diameter/2+3]) cube([ball_diameter+4,ball_diameter+4,10]);
//Inside:    
    translate([0,0,-5]) cylinder(h=ball_diameter/2+4, r=ball_diameter/2+nozzle_dia); 
    translate([0,0,ball_diameter/2-1]) sphere(r=ball_diameter/2+nozzle_dia);  
//Mounting holes:    
    translate([-mountingHoles_width/2,0,-1]) cylinder(h=caster_height, r=mountingScrew_dia/2+nozzle_dia/2,$fn=16); 
    translate([mountingHoles_width/2,0,-1]) cylinder(h=caster_height, r=mountingScrew_dia/2+nozzle_dia/2,$fn=16); 
    
    translate([-mountingHoles_width/2,ball_diameter+5,-1]) cylinder(h=caster_height, r=mountingScrew_dia/2+nozzle_dia/2,$fn=16); 
    translate([mountingHoles_width/2,ball_diameter+5,-1]) cylinder(h=caster_height, r=mountingScrew_dia/2+nozzle_dia/2,$fn=16);
//Washer area:   
    translate([0,ball_diameter+5,caster_height-ball_diameter-washer_thickness]) cylinder(h=2*washer_thickness, r=washer_dia/2+nozzle_dia); 


}
