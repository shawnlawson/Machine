uniform sampler2DRect tex;
uniform float multiplier;

void main()
{
	gl_FragColor = gl_Color * max(texture2DRect(tex, gl_TexCoord[0].xy), vec4(multiplier));
}
