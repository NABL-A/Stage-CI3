VARYING float vHeight;

void MAIN()
{
    float h = 0.0;
    float sigma2 = sigma * sigma;

    vec2 pos = vec2(VERTEX.x, VERTEX.z);

    if (sensorCount > 0) {
        vec2 d = pos - sensor0.xy;
        h += sensor0.z * exp(-dot(d, d) / (2.0 * sigma2));
    }
    if (sensorCount > 1) {
        vec2 d = pos - sensor1.xy;
        h += sensor1.z * exp(-dot(d, d) / (2.0 * sigma2));
    }
    if (sensorCount > 2) {
        vec2 d = pos - sensor2.xy;
        h += sensor2.z * exp(-dot(d, d) / (2.0 * sigma2));
    }
    if (sensorCount > 3) {
        vec2 d = pos - sensor3.xy;
        h += sensor3.z * exp(-dot(d, d) / (2.0 * sigma2));
    }
    if (sensorCount > 4) {
        vec2 d = pos - sensor4.xy;
        h += sensor4.z * exp(-dot(d, d) / (2.0 * sigma2));
    }
    if (sensorCount > 5) {
        vec2 d = pos - sensor5.xy;
        h += sensor5.z * exp(-dot(d, d) / (2.0 * sigma2));
    }
    if (sensorCount > 6) {
        vec2 d = pos - sensor6.xy;
        h += sensor6.z * exp(-dot(d, d) / (2.0 * sigma2));
    }
    if (sensorCount > 7) {
        vec2 d = pos - sensor7.xy;
        h += sensor7.z * exp(-dot(d, d) / (2.0 * sigma2));
    }

    h = clamp(h, 0.0, 1.0);
    vHeight = h;

    POSITION = MODELVIEWPROJECTION_MATRIX * vec4(VERTEX.x,
                                                  h * heightScale,
                                                  VERTEX.z,
                                                  1.0);
}
