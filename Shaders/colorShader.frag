#version 330
// The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

// This is a 3 omponent float verctor that gets outputted to the screen
// for each pixel
out vec4 color;

// uniform float time;
uniform sampler2D mySampler;

void main(void){
    // cos(x) returns a number between -1 and 1.
    // you simply do (cos(x) + 1.0) * 0.5
    // to get a number between 0 and 1

    vec4 textureColor = texture(mySampler, fragmentUV);

    // make creazy colors using time and position
    // color = textureColor * fragmentColor;
    
    color = fragmentColor * textureColor;
}