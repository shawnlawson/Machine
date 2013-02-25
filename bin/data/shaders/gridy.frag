uniform float alpha;
uniform float waveAlpha;
uniform vec2  BrickSize;
uniform vec2  BrickPct;
uniform float time;
uniform vec2 resolution;
uniform vec2 offset;

vec2 Distort(vec2 p)
{
    float theta  = atan(p.y, p.x);
    float radius = length(p);
    radius = pow(radius, 1.3);
    p.x = radius * cos(theta);
    p.y = radius * sin(theta);
    return 0.5 * (p + 1.0);
}

vec4 pattern(vec2 p)
{
	vec2 m=mod(p.xy+p.x+p.y,2.)-1.;
	return vec4(length(m+p*0.1));
}

float hash(const float n)
{
	return fract(sin(n)*43758.5453);
}

float noise(const vec3 x)
{
	vec3 p=floor(x);
	vec3 f=fract(x);

    	f=f*f*(3.0-2.0*f);

    	float n=p.x+p.y*57.0+p.z*43.0;

    	float r1=mix(mix(hash(n+0.0),hash(n+1.0),f.x),mix(hash(n+57.0),hash(n+57.0+1.0),f.x),f.y);
    	float r2=mix(mix(hash(n+43.0),hash(n+43.0+1.0),f.x),mix(hash(n+43.0+57.0),hash(n+43.0+57.0+1.0),f.x),f.y);

	return mix(r1,r2,f.z);
}

void main()
{
    vec4  color, BrickColor = vec4(0.25, 0.25, 0.25, 1.0), MortarColor = vec4(0.25, 0.25, 0.25, 0.0);
    vec2  position, useBrick;
    
    position = (gl_FragCoord.xy+offset.xy) / BrickSize ;

    position = fract(position);

    	useBrick = step(position, BrickPct);

    color  = mix(color, BrickColor, useBrick.x);
	color += mix(color, BrickColor, useBrick.y);

	vec2 position2 = ( gl_FragCoord.xy / resolution.xy );
	float off = noise(position2.xyx + time);
	vec4 c  = pattern(Distort(position2+off+offset.xy));

	color.a = min(color.a, pow(c.a, waveAlpha)) * alpha;
    gl_FragColor = color;
}