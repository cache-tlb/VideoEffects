#version 330

uniform sampler2D tDiffuse;
uniform float amount;
uniform float angle;

in vec2 vUv;
out vec4 outputF;

void main() {
	vec2 offset = amount * vec2( cos(angle), sin(angle));
	vec4 cr = texture2D(tDiffuse, vUv + offset);
	vec4 cga = texture2D(tDiffuse, vUv);
	vec4 cb = texture2D(tDiffuse, vUv - offset);
	outputF = vec4(cr.r, cga.g, cb.b, cga.a);
}
