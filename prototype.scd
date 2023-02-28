(
SynthDef(\detune, {
	arg bufnum = 0;
	var sigDry, sig, env, mod, fxDur;
	var freq1, freq2, q1, q2;
	var filt1, filt2, sigWet, out;

	fxDur = rrand(2, 6);
	freq1 = rrand(500, 1200);
	freq2 = rrand(200, 3000);
	q1 = rrand(0.3, 0.6);
	q2 = rrand(0.3, 0.6);
	sigDry = PlayBuf.ar(2, bufnum, 1.0);
	sig = BRF.ar(sigDry, freq1, q1);
	sig = BRF.ar(sig, freq2, q2);
	filt1 = Delay2.ar(BPF.ar(sigDry, freq1, q1));
	filt2 = Delay2.ar(BPF.ar(sigDry, freq2, q2));
	sigWet = Mix.ar([sig, filt1, filt2]);
	out = OffsetOut.ar(0, sigWet);
}).add;
)