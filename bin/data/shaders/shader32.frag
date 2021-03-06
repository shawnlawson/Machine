#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
#define DOTSIZEX 8.0
#define DOTSIZEY 8.0

void main( void ) {
	//some Variables that are being initialized
	vec2 DotResolution = floor(resolution / vec2(DOTSIZEX,DOTSIZEY));
	float intensity = 0.0;
	vec2 Center = floor((DotResolution - 1.0) / 2.0);
	float timeIndex = mod(time, 1.0);
	if( timeIndex < 0.1)timeIndex = 0.1;
	
	//the real stuff
	vec2 CurrentDot = floor(gl_FragCoord.xy / vec2(DOTSIZEX, DOTSIZEY));
	float CurrentX = floor(gl_FragCoord.x / DOTSIZEX + Center.x);
	float CurrentY = cos(time*1.5)*sin(CurrentX / 4.0 + time)*10.0+Center.y;
	
	float dist = mod(abs(gl_FragCoord.y - (floor(CurrentY) * DOTSIZEY)), 32.0);
	
	//is our Current FragCoord on the Dot?
	if(dist < 4.0 || (dist < 12.0 && dist > 8.0))
	{
		intensity = dist/6.0;
	}
	
	vec3 FinalColor = vec3(0.88) * intensity;
	gl_FragColor = vec4(FinalColor, 1.0);
}