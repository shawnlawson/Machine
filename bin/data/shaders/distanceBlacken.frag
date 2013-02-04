#version 120

void main(void)
{
	vec4 black= vec4(0.0,0.0,0.0,1.0);
	vec4 green = vec4(0.0, 1.0, 0.0, 1.0);
	if( gl_FragCoord.y > 600.0){
		gl_FragColor = mix(black, gl_Color, (gl_FragCoord.y-600.0)/180.0);
//		gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
	}else{
//		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
}