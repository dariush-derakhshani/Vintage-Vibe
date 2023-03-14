(
Ndef(\VintageVibe, {
	arg inputGain = 1.0, noiseGain = 0.2, wet = 1.0, range = 100.0, rate = 0.33;
	var input, sig, out, noise;

	input = SoundIn.ar([0,1], 1.0) * inputGain;
	sig = FreqShift.ar(
		input,
		[
			LFNoise1.kr(rate).range((-1*range/2), (range/2)) * wet,
			LFNoise1.kr(rate).range((-1*range/2), (range/2)) * wet

	], 0.0);
	noise = Dust.ar(
		[
			LFNoise1.kr(rate).range(1.0, 10.0),
			LFNoise1.kr(rate).range(10.0, 20.0)],
		[
			LFNoise1.kr(rate).range(0.0005, 0.1),
			LFNoise1.kr(rate).range(0.0005, 0.1)
	]);
	sig = sig * 0.6.linlin(0.0, 1.0, 0.0, 1.0);
	sig = (noise * noiseGain) + sig;
	out = Out.ar(0, sig);
};
)
);

Ndef(\VintageVibe).set(\inputGain, 1)

GUI

(
~gui = Window("Vintage Vibe").background_(Color(0.6, 0.7, 0.6, 1.0)).front;

~wet = Slider(~gui, Rect(70, 15, 200, 20))
.knobColor_(Color(0.6, 0.7, 0.6, 1.0))
.background_(Color(0.8, 0.6, 0.6, 1.0))
.value_(0.0)
.action_({arg slider; Ndef(\VintageVibe).set(\wet, slider.value); ~wetBox.value_(slider.value)});

~wetBox = NumberBox(~gui, Rect(280, 10, 50, 30))
.background_(Color.white)
.value_(0.0)
.decimals_(2)
.action_({
	arg slider;
	Ndef(\VintageVibe).set(\wet, slider.value)});
~wetLabel = StaticText(~gui, Rect(10, 10, 60, 30))
.string_("[Detune]")
.font_(Font("Monospace", 10, true))
.background_(Color(0.6, 0.7, 0.6, 1.0))
.stringColor_(Color.black);

~inputGain = Knob(~gui, Rect(70, 50, 40, 40))
.background_(Color.white)
.value_(1.0)
.action_({arg slider; Ndef(\VintageVibe).set(\inputGain, slider.value)});

~gainLabel = StaticText(~gui, Rect(10, 50, 60, 30))
.string_("[Gain]")
.font_(Font("Monospace", 10, true))
.background_(Color(0.6, 0.7, 0.6, 1.0))
.stringColor_(Color.black);
)
