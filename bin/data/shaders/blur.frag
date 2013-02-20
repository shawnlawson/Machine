uniform sampler2DRect tex;
uniform float radius;
void main()
{
    vec2 st = gl_TexCoord[0].st;
    const float total = (1. + 8. + 28. + 56.) * 4.0 + 70.;
    vec4 blur = vec4(0.0);
    blur += (1. / total) * texture2DRect(tex, st - radius * vec2(4. / 4., 0.));
    blur += (8. / total)  * texture2DRect(tex, st - radius * vec2(3. / 4., 0.));
    blur += (28. / total)  * texture2DRect(tex, st - radius * vec2(2. / 4., 0.));
    blur += (56. / total)  * texture2DRect(tex, st - radius * vec2(1. / 4., 0.));

    blur +=  (70. / total) * texture2DRect(tex, st);

    blur += (1. / total) * texture2DRect(tex, st + radius * vec2(4. / 4., 0.));
    blur += (8. / total)  * texture2DRect(tex, st + radius * vec2(3. / 4., 0.));
    blur += (28. / total)  * texture2DRect(tex, st + radius * vec2(2. / 4., 0.));
    blur += (56. / total)  * texture2DRect(tex, st + radius * vec2(1. / 4., 0.));

    blur += (1. / total) * texture2DRect(tex, st - radius * vec2(0., 4. / 4.));
    blur += (8. / total)  * texture2DRect(tex, st - radius * vec2(0., 3. / 4.));
    blur += (28. / total)  * texture2DRect(tex, st - radius * vec2(0., 2. / 4.));
    blur += (56. / total)  * texture2DRect(tex, st - radius * vec2(0., 1. / 4.));

    //  blur +=  (70. / total) * texture2DRect(tex, st);

    blur += (1. / total) * texture2DRect(tex, st + radius * vec2(0., 4. / 4.));
    blur += (8. / total)  * texture2DRect(tex, st + radius * vec2(0., 3. / 4.));
    blur += (28. / total)  * texture2DRect(tex, st + radius * vec2(0., 2. / 4.));
    blur += (56. / total)  * texture2DRect(tex, st + radius * vec2(0., 1. / 4.));

    gl_FragColor = blur;
}
