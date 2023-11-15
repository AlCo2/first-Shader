float sdEquilateralTriangle( in vec2 p, in float r )
{
    const float k = sqrt(3.0);
    p.x = abs(p.x) - r;
    p.y = p.y + r/k;
    if( p.x+k*p.y>0.0 ) p = vec2(p.x-k*p.y,-k*p.x-p.y)/2.0;
    p.x -= clamp( p.x, -2.0*r, 0.0 );
    return -length(p)*sign(p.y);
}
vec3 palette( in float t)
{

    vec3 a = vec3(0.758, 0.388, 1.388);
    vec3 b = vec3(0.297, 0.516, -1.025);
    vec3 c = vec3(-2.100, -2.288, 0.65);
    vec3 d = vec3(-0.483, -1.673, -1.373);
    return a + b*cos( 6.28318*(c*t+d) );
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = (fragCoord*2.0-iResolution.xy)/iResolution.y;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);
    
    for(float i=0.0;i<4.0;i++){
        uv *= 1.5;
        uv = fract(uv);
        uv-=0.5;
        float d = sdEquilateralTriangle(uv, 0.3f) * exp(-length(uv0));
        vec3 col = palette(length(uv0) + i*.4 +iTime*.4);
        d = cos(d*8. + iTime)/4.;
        d = abs(d);
        d = pow(0.01/d, 1.2);
        finalColor = col * d;
    }
    
    fragColor = vec4(finalColor, 1.0);
    
}