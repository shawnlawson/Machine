
vec3 nrand3( vec2 co )
{
	float x = sin( co.x*8.3e-3 + co.y );
	return fract( x*vec3(1.3e5, 8.3e5, 1.63e5) );
}

void main(void)
{
//	vec2 p = vec2(0.5, 0.5) + gl_FragCoord.xy * vec2(2,2) / resolution.xy;
vec2 p = gl_FragCoord.xy;
	float ofs = fract(0.0) * (0.1+11.0*p.x);
	vec2 seed = p;
	seed += p.y * vec2(ofs, 0.0);
//	seed = floor(seed * resolution);
	vec3 rnd = nrand3( seed ) ;
float value = pow(rnd.g, 8.0);
//rnd = vec3(pow(rnd.r, 8.0), pow(rnd.g, 8.0), pow(rnd.b, 8.0));

//	gl_FragColor = vec4(rnd, 1.0);
gl_FragColor = vec4(value, value, value, 1.0);
}
