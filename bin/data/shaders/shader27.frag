#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

	if(abs(gl_FragCoord.y - (sin((gl_FragCoord.x+resolution.x)/10.0)*80.0+resolution.y/2.0)) < 4.0)gl_FragColor = vec4(1.0);
}