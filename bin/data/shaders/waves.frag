uniform float time;
uniform float alpha;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float offset;


void main( void )
{

	vec2 uPos = ( gl_FragCoord.xy / resolution.xy );//normalize wrt y axis
	//suPos -= vec2((resolution.x/resolution.y)/2.0, 0.0);//shift origin to center
	
	uPos.y -= .4;
	uPos.x += offset;
	
	vec3 color = vec3(0.0);
	float vertColor = 0.0;
	const float k = 9.;
	for( float i = 1.0; i < k; ++i )
	{
		float t = time * exp(0.1*mouse.x) * (1.0);
	
		uPos.y += exp(3.0*mouse.y) * sin( uPos.x*exp(i) - t) * 0.01;
		float fTemp = abs(1.0/(50.0*k) / uPos.y);
		vertColor += fTemp;
		color += vec3(  fTemp*i/k, fTemp*i/k,  fTemp*i/k );
	}
	
	gl_FragColor = vec4(color, alpha);;
}