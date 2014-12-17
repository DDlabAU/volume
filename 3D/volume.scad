inside_width=139;
grab_length=50;
height=35;
fatness=4;
$fn=25;
servo_width=21;
servo_length=42;
servo_spline_offset=9.66;

  translate([0,0,0]){
  	difference()
  	{
  	union(){

  			rotate([90,0,0]){cube([inside_width+2*fatness,height,fatness]);}
  			rotate([90,0,90]){color("lime"){cube([grab_length,height,fatness]);}}
  			translate([inside_width+fatness,0,0]){rotate([90,0,90]){color("red"){cube([grab_length,height,fatness]);}}}
  			}


		translate([25-servo_spline_offset,fatness/2,height/2-servo_width/2]){
			rotate([90,0,0 ]){
 		translate([0,servo_width/2-servo_width/4,0])
 		{

		cylinder(r=1,h=fatness*2);
		translate([0,9.5,0]){cylinder(r=1,h=fatness*2);}
		translate([50,0,0]){cylinder(r=1,h=fatness*2);}
		translate([50,9.5,0]){cylinder(r=1,h=fatness*2);}
	    }
		translate([4.25-1,0,0]){cube([servo_length+2,servo_width,2*fatness]);}}}



	}
}