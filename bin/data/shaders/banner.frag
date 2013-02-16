uniform float dotSize;
uniform float freq;
uniform float time; //continuous if time doesn't ping-pong
uniform float height;
uniform vec2 resolution; // viewport draw size shader builder 1024, 1024

void main( void ) {
	// (fragment X+position X/-spin speed + time ) * vertical size + position Y < dot or line length
	if(abs(gl_FragCoord.y - (sin((gl_FragCoord.x+resolution.x)/-freq+time)*height+resolution.y/2.0)) < dotSize)
		gl_FragColor = vec4(1.0);
//	else
//		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}