uniform float time;
uniform sampler2DRect tex;
uniform float alignment;                           
uniform float brightness;
uniform float rows;                     


void main(void)
{
	vec2 st = gl_TexCoord[0].st;
	vec2 uv = vec2(1.0);
	vec3 col = vec3(0.0);
 

	col.r = texture2DRect(tex, vec2(st.x+alignment, st.y)).r;
	col.g = texture2DRect(tex, vec2(st.x+0.000,st.y)).g;
	col.b = texture2DRect(tex, vec2(st.x-alignment, st.y)).b;

	col = clamp(col * 0.5 + 0.5 * col * col * 1.2,0.0,1.0);


		uv = 0.5 + (1.0/st-0.5)*((1.0-brightness) + brightness*sin(0.2*time));                                                           
     	col *= 0.5 + 0.5 * 16.0 * uv.x * uv.y * (1.0-uv.x) * (1.0-uv.y);


	col *= vec3(0.85,1.0,0.75);
	col *= 0.9 + 0.1 * sin(10.0 * time + st.y * rows);
	col *= 0.97 + 0.03 * sin(110.0 * time);

	float a = col.r;
     gl_FragColor = vec4(col,a);
}