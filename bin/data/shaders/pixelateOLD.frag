uniform sampler2DRect src_tex_unit0;
uniform float pixel_size;

void main(void)
{
    float d = 1.0 / pixel_size;
    vec2 tex_coords = gl_TexCoord[0].st;
	vec2 pix = vec2(pixel_size, pixel_size);
	vec2 location = pixel_size * ( floor( gl_TexCoord[0].st/pixel_size ) + d );

//	float fx = floor(tex_coords.s  / pixel_size);
//	float fy = floor(tex_coords.t  / pixel_size);
	
 //   float s = pixel_size * (fx + d);
 //   float t = pixel_size * (fy + d);
    
    gl_FragColor = texture2DRect(src_tex_unit0, location);
}
