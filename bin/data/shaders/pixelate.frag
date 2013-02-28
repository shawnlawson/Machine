uniform sampler2DRect tex0;
uniform float pixel_size;

void main(void)
{
	vec2 location = pixel_size * ( floor( gl_TexCoord[0].st/pixel_size )  );
    gl_FragColor = texture2DRect(tex0, location);
}
