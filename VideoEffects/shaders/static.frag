#version 330

uniform sampler2D tDiffuse;
uniform float time;
uniform float amount;
uniform float size;

in vec2 vUv;
out vec4 outputF;

float rand(vec2 co){
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
	vec2 p = vUv;
	vec4 color = texture2D(tDiffuse, p);
	vec2 fragCoord = gl_FragCoord;
	float xs = floor(fragCoord.x / size);
	float ys = floor(fragCoord.y / size);
	vec4 snow = vec4(rand(vec2(xs * time,ys * time))*amount);

	//outputF = color + amount * ( snow - color ); //interpolate
	outputF = color+ snow; //additive
}
