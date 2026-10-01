VARYING float vHeight;

void MAIN()
{
    float t = clamp(vHeight, 0.0, 1.0);

    vec3 col;
    if (t < 0.33) {
        float f = t / 0.33;
        col = mix(vec3(0.0, 0.0, 1.0), vec3(0.0, 1.0, 1.0), f);
    } else if (t < 0.66) {
        float f = (t - 0.33) / 0.33;
        col = mix(vec3(0.0, 1.0, 1.0), vec3(1.0, 1.0, 0.0), f);
    } else {
        float f = (t - 0.66) / 0.34;
        col = mix(vec3(1.0, 1.0, 0.0), vec3(1.0, 0.0, 0.0), f);
    }

    BASE_COLOR = vec4(col, 1.0);
}
