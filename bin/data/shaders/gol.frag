#version 120
#extension GL_ARB_draw_buffers: enable
#extension GL_ARB_texture_rectangle: enable

uniform sampler2DRect tex0;
uniform float alpha;

void main() {
	// retrieve the texture coordinate
	vec2 c = gl_TexCoord[0].xy;

	// and the current pixel
	vec3 current = texture2DRect(tex0, c).rgb;

	// count the neightbouring pixels with a value greater than zero
	vec3 neighbours = vec3(0.0);
	neighbours += vec3(greaterThan(texture2DRect(tex0, c + vec2(-1,-1)).rgb, vec3(0.0)));
	neighbours += vec3(greaterThan(texture2DRect(tex0, c + vec2(-1, 0)).rgb, vec3(0.0)));
	neighbours += vec3(greaterThan(texture2DRect(tex0, c + vec2(-1, 1)).rgb, vec3(0.0)));
	neighbours += vec3(greaterThan(texture2DRect(tex0, c + vec2( 0,-1)).rgb, vec3(0.0)));
	neighbours += vec3(greaterThan(texture2DRect(tex0, c + vec2( 0, 1)).rgb, vec3(0.0)));
	neighbours += vec3(greaterThan(texture2DRect(tex0, c + vec2( 1,-1)).rgb, vec3(0.0)));
	neighbours += vec3(greaterThan(texture2DRect(tex0, c + vec2( 1, 0)).rgb, vec3(0.0)));
	neighbours += vec3(greaterThan(texture2DRect(tex0, c + vec2( 1, 1)).rgb, vec3(0.0)));

	// check if the current pixel is alive
	vec3 live = vec3(greaterThan(current, vec3(0.0)));

	// resurect if we are not live, and have 3 live neighrbours
	current += (1.0-live) * vec3(equal(neighbours, vec3(3.0)));

	// kill if we do not have either 3 or 2 neighbours
	current *= vec3(equal(neighbours, vec3(2.0))) + vec3(equal(neighbours, vec3(3.0)));

	// fade the current pixel as it ages
	current -= vec3(greaterThan(current, vec3(0.4)))*0.05;

	// write out the pixel
	gl_FragColor = vec4(current, alpha);
}