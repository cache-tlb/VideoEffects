#version 330

uniform float opacity;
uniform sampler2D tDiffuse;
uniform bool flipY;
in vec2 vUv;
out vec4 outputF;

void main() {
	vec4 texel;
	if (flipY) texel = texture2D( tDiffuse, vec2(vUv.x, 1.0 - vUv.y) );
	else texel = texture2D( tDiffuse, vUv );
	outputF = opacity * texel;
}
