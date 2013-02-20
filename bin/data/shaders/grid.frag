uniform vec2 resolution;
uniform float offset;
vec3 color(vec2 pos, float d){
	vec2 uv = abs(fract(pos*50.)-.15)*d*5.0;
	return vec3(1.-min(uv.x, uv.y));
}

void main( void ) {
	vec2 pos = vec2((gl_FragCoord.x * 1.0) / resolution.y, (gl_FragCoord.y * 1.0) / resolution.x);
pos.x += offset;
	float d = length(pos);

	gl_FragColor = vec4(.0, 1., 0., color(pos, d));//vec4(color(pos, d)*vec3(0.0, 1.0,0.0), 1);
}