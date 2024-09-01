/*
 * Test of using structures to organise the flat list
 * you get out of the Design Tool. Version 2, with ILDA
 */
#include <Audio.h>

// This topology cribbed straight from T4_LS_VI-8-4

// GUItool: begin automatically generated code
AudioSynthWaveformDc     OscModDc;       //xy=162,1222
AudioSynthWaveform       OscMod2;        //xy=164,1294
AudioSynthWaveform       OscMod1;        //xy=165,1258
AudioMixer4              Y2_ModMix;      //xy=408,815
AudioMixer4              Y3_ModMix;      //xy=408,882
AudioMixer4              Y4_ModMix;      //xy=408,949
AudioMixer4              Y1_ModMix;      //xy=409,749
AudioMixer4              Y5_ModMix;      //xy=408,1017
AudioMixer4              Y6_ModMix;      //xy=408,1085
AudioMixer4              Y7_ModMix;      //xy=408,1153
AudioMixer4              Y8_ModMix;      //xy=408,1222
AudioMixer4              X2_ModMix;      //xy=408,1367
AudioMixer4              X3_ModMix;      //xy=408,1433
AudioMixer4              X4_ModMix;      //xy=408,1498
AudioMixer4              X8_ModMix;      //xy=407,1763
AudioMixer4              X1_ModMix;      //xy=409,1302
AudioMixer4              X5_ModMix;      //xy=408,1564
AudioMixer4              X6_ModMix;      //xy=408,1630
AudioMixer4              X7_ModMix;      //xy=409,1697
AudioPlayILDA            playILDA1;      //xy=543,586
AudioSynthWaveform       ILD_Mod;        //xy=548,669
AudioSynthWaveform       B_Mod2;         //xy=552,135
AudioSynthWaveform       R_Mod1;         //xy=552,330
AudioSynthWaveform       B_Mod1;         //xy=553,100
AudioSynthWaveform       R_Mod2;         //xy=552,365
AudioSynthWaveform       G_Mod1;         //xy=553,217
AudioSynthWaveform       G_Mod2;         //xy=553,253
AudioSynthWaveform       Y2_Osc;         //xy=554,795
AudioSynthWaveformDc     R_Dc;           //xy=556,296
AudioSynthWaveformDc     G_Dc;           //xy=557,182
AudioSynthWaveform       Y1_Osc;         //xy=555,729
AudioSynthWaveform       Y5_Osc;         //xy=554,998
AudioSynthWaveform       Y6_Osc;         //xy=554,1066
AudioSynthWaveform       Y7_Osc;         //xy=554,1135
AudioSynthWaveform       Y4_Osc;         //xy=555,931
AudioSynthWaveform       Y8_Osc;         //xy=554,1203
AudioSynthWaveformDc     B_Dc;           //xy=559,66
AudioSynthWaveform       Y3_Osc;         //xy=556,863
AudioSynthWaveform       X1_Osc;         //xy=555,1285
AudioSynthWaveform       X5_Osc;         //xy=554,1544
AudioSynthWaveform       X2_Osc;         //xy=555,1348
AudioSynthWaveform       X6_Osc;         //xy=554,1611
AudioSynthWaveform       X3_Osc;         //xy=555,1414
AudioSynthWaveform       X7_Osc;         //xy=555,1679
AudioSynthWaveform       X4_Osc;         //xy=556,1478
AudioSynthWaveform       X8_Osc;         //xy=555,1743
AudioEffectMultiply      Y1_mult;        //xy=702,742
AudioEffectMultiply      Y2_mult;        //xy=702,808
AudioEffectMultiply      Y3_mult;        //xy=702,877
AudioEffectMultiply      Y4_mult;        //xy=702,946
AudioEffectMultiply      Y8_Mult;        //xy=701,1217
AudioEffectMultiply      Y6_Mult;        //xy=702,1079
AudioEffectMultiply      Y7_Mult;        //xy=702,1150
AudioEffectMultiply      Y5_Mult;        //xy=703,1012
AudioEffectMultiply      X1_mult;        //xy=702,1299
AudioEffectMultiply      X5_Mult;        //xy=701,1559
AudioEffectMultiply      X2_mult;        //xy=702,1364
AudioEffectMultiply      X3_mult;        //xy=702,1428
AudioEffectMultiply      X7_Mult;        //xy=701,1693
AudioEffectMultiply      X4_mult;        //xy=702,1494
AudioEffectMultiply      X8_Mult;        //xy=701,1758
AudioEffectMultiply      X6_Mult;        //xy=702,1625
AudioSynthWaveform       Z_RotWave;      //xy=749,626
AudioEffectMultiply      Y_ILDmult;      //xy=752,589
AudioEffectMultiply      Z_ILDmult;      //xy=752,662
AudioEffectMultiply      X_ILDmult;      //xy=753,553
AudioSynthWaveformDc     I_ModDc;        //xy=757,398
AudioMixer4              B_Mix;          //xy=760,109
AudioMixer4              R_Mix;          //xy=760,338
AudioMixer4              G_Mix;          //xy=761,226
AudioSynthWaveform       I_Mod1;         //xy=761,434
AudioSynthWaveform       I_Mod2;         //xy=761,469
AudioRecordQueue         queue1;         //xy=762,515
AudioSynthWaveformDc     Y_OscMrSize;    //xy=906,1169
AudioSynthWaveformDc     X_OscMrSize;    //xy=906,1273
AudioSynthWaveform       X_RotWave;      //xy=912,682
AudioEffectRotator       Z_Rotate;       //xy=916,588
AudioSynthWaveform       Y_mrMod2;       //xy=915,1238
AudioSynthWaveform       Y_mrMod1;       //xy=917,1204
AudioSynthWaveform       X_mrMod1;       //xy=917,1308
AudioSynthWaveform       X_mrMod2;       //xy=917,1345
AudioMixer4              Y_Mix1;         //xy=924,847
AudioMixer4              Y_Mix2;         //xy=926,1116
AudioMixer4              X_Mix1;         //xy=925,1396
AudioMixer4              X_Mix2;         //xy=925,1661
AudioMixer4              I_ModMix;       //xy=930,438
AudioMixer4              Y_mrModMix;     //xy=1124,1211
AudioMixer4              X_mrModMix;     //xy=1125,1316
AudioSynthWaveformDc     mrIntenseDC;    //xy=1132,387
AudioSynthWaveform       Y_RotWave;      //xy=1135,609
AudioEffectRotator       X_Rotate;       //xy=1138,662
AudioEffectMultiply      B_Mult;         //xy=1145,117
AudioEffectMultiply      G_Mult;         //xy=1145,231
AudioEffectMultiply      R_Mult;         //xy=1147,341
AudioMixerSummer         Y_Sum;          //xy=1147,972
AudioMixerSummer         X_Sum;          //xy=1147,1525
AudioEffectMultiply      Y_mrModMult;    //xy=1354,1090
AudioEffectMultiply      X_mrModMult;    //xy=1354,1418
AudioEffectRotator       Y_Rotate;       //xy=1364,595
AudioEffectMultiply      R_mrMult;       //xy=1368,334
AudioEffectMultiply      B_mrMult;       //xy=1369,110
AudioEffectMultiply      G_mrMult;       //xy=1369,224
AudioSynthWaveformDc     Y_mrPos;        //xy=1494,565
AudioSynthWaveformDc     X_mrPos;        //xy=1497,634
AudioMixer4              Y_mrMix;        //xy=1674,584
AudioMixer4              X_mrMix;        //xy=1674,654
AudioOutputTDM           tdm1;           //xy=1852,578

AudioConnection          patchCord1(OscModDc, 0, X1_ModMix, 0);
AudioConnection          patchCord2(OscModDc, 0, X2_ModMix, 0);
AudioConnection          patchCord3(OscModDc, 0, X3_ModMix, 0);
AudioConnection          patchCord4(OscModDc, 0, X4_ModMix, 0);
AudioConnection          patchCord5(OscModDc, 0, Y1_ModMix, 0);
AudioConnection          patchCord6(OscModDc, 0, Y2_ModMix, 0);
AudioConnection          patchCord7(OscModDc, 0, Y3_ModMix, 0);
AudioConnection          patchCord8(OscModDc, 0, Y4_ModMix, 0);
AudioConnection          patchCord9(OscModDc, 0, Y5_ModMix, 0);
AudioConnection          patchCord10(OscModDc, 0, Y6_ModMix, 0);
AudioConnection          patchCord11(OscModDc, 0, Y7_ModMix, 0);
AudioConnection          patchCord12(OscModDc, 0, X5_ModMix, 0);
AudioConnection          patchCord13(OscModDc, 0, X6_ModMix, 0);
AudioConnection          patchCord14(OscModDc, 0, X7_ModMix, 0);
AudioConnection          patchCord15(OscModDc, 0, X8_ModMix, 0);
AudioConnection          patchCord16(OscModDc, 0, Y8_ModMix, 0);
AudioConnection          patchCord17(OscMod2, 0, X1_ModMix, 2);
AudioConnection          patchCord18(OscMod2, 0, X2_ModMix, 2);
AudioConnection          patchCord19(OscMod2, 0, X3_ModMix, 2);
AudioConnection          patchCord20(OscMod2, 0, X4_ModMix, 2);
AudioConnection          patchCord21(OscMod2, 0, Y1_ModMix, 2);
AudioConnection          patchCord22(OscMod2, 0, Y2_ModMix, 2);
AudioConnection          patchCord23(OscMod2, 0, Y3_ModMix, 2);
AudioConnection          patchCord24(OscMod2, 0, Y4_ModMix, 2);
AudioConnection          patchCord25(OscMod2, 0, Y5_ModMix, 2);
AudioConnection          patchCord26(OscMod2, 0, Y6_ModMix, 2);
AudioConnection          patchCord27(OscMod2, 0, Y7_ModMix, 2);
AudioConnection          patchCord28(OscMod2, 0, X5_ModMix, 2);
AudioConnection          patchCord29(OscMod2, 0, X6_ModMix, 2);
AudioConnection          patchCord30(OscMod2, 0, X7_ModMix, 2);
AudioConnection          patchCord31(OscMod2, 0, X8_ModMix, 2);
AudioConnection          patchCord32(OscMod2, 0, Y8_ModMix, 2);
AudioConnection          patchCord33(OscMod1, 0, X1_ModMix, 1);
AudioConnection          patchCord34(OscMod1, 0, X2_ModMix, 1);
AudioConnection          patchCord35(OscMod1, 0, X3_ModMix, 1);
AudioConnection          patchCord36(OscMod1, 0, X4_ModMix, 1);
AudioConnection          patchCord37(OscMod1, 0, Y1_ModMix, 1);
AudioConnection          patchCord38(OscMod1, 0, Y2_ModMix, 1);
AudioConnection          patchCord39(OscMod1, 0, Y3_ModMix, 1);
AudioConnection          patchCord40(OscMod1, 0, Y4_ModMix, 1);
AudioConnection          patchCord41(OscMod1, 0, Y5_ModMix, 1);
AudioConnection          patchCord42(OscMod1, 0, Y6_ModMix, 1);
AudioConnection          patchCord43(OscMod1, 0, Y7_ModMix, 1);
AudioConnection          patchCord44(OscMod1, 0, X5_ModMix, 1);
AudioConnection          patchCord45(OscMod1, 0, X6_ModMix, 1);
AudioConnection          patchCord46(OscMod1, 0, X7_ModMix, 1);
AudioConnection          patchCord47(OscMod1, 0, X8_ModMix, 1);
AudioConnection          patchCord48(OscMod1, 0, Y8_ModMix, 1);
AudioConnection          patchCord49(Y2_ModMix, 0, Y2_mult, 1);
AudioConnection          patchCord50(Y3_ModMix, 0, Y3_mult, 1);
AudioConnection          patchCord51(Y4_ModMix, 0, Y4_mult, 1);
AudioConnection          patchCord52(Y1_ModMix, 0, Y1_mult, 1);
AudioConnection          patchCord53(Y5_ModMix, 0, Y5_Mult, 1);
AudioConnection          patchCord54(Y6_ModMix, 0, Y6_Mult, 1);
AudioConnection          patchCord55(Y7_ModMix, 0, Y7_Mult, 1);
AudioConnection          patchCord56(Y8_ModMix, 0, Y8_Mult, 1);
AudioConnection          patchCord57(X2_ModMix, 0, X2_mult, 1);
AudioConnection          patchCord58(X3_ModMix, 0, X3_mult, 1);
AudioConnection          patchCord59(X4_ModMix, 0, X4_mult, 1);
AudioConnection          patchCord60(X8_ModMix, 0, X8_Mult, 1);
AudioConnection          patchCord61(X1_ModMix, 0, X1_mult, 1);
AudioConnection          patchCord62(X5_ModMix, 0, X5_Mult, 1);
AudioConnection          patchCord63(X6_ModMix, 0, X6_Mult, 1);
AudioConnection          patchCord64(X7_ModMix, 0, X7_Mult, 1);
AudioConnection          patchCord65(playILDA1, 0, queue1, 0);
AudioConnection          patchCord66(playILDA1, 0, X_ILDmult, 0);
AudioConnection          patchCord67(playILDA1, 1, Y_ILDmult, 0);
AudioConnection          patchCord68(playILDA1, 2, Z_ILDmult, 0);
AudioConnection          patchCord69(playILDA1, 3, R_Mix, 3);
AudioConnection          patchCord70(playILDA1, 4, G_Mix, 3);
AudioConnection          patchCord71(playILDA1, 5, B_Mix, 3);
AudioConnection          patchCord72(ILD_Mod, 0, X_ILDmult, 1);
AudioConnection          patchCord73(ILD_Mod, 0, Y_ILDmult, 1);
AudioConnection          patchCord74(ILD_Mod, 0, Z_ILDmult, 1);
AudioConnection          patchCord75(B_Mod2, 0, B_Mix, 2);
AudioConnection          patchCord76(R_Mod1, 0, R_Mix, 1);
AudioConnection          patchCord77(B_Mod1, 0, B_Mix, 1);
AudioConnection          patchCord78(R_Mod2, 0, R_Mix, 2);
AudioConnection          patchCord79(G_Mod1, 0, G_Mix, 1);
AudioConnection          patchCord80(G_Mod2, 0, G_Mix, 2);
AudioConnection          patchCord81(Y2_Osc, 0, Y2_mult, 0);
AudioConnection          patchCord82(R_Dc, 0, R_Mix, 0);
AudioConnection          patchCord83(G_Dc, 0, G_Mix, 0);
AudioConnection          patchCord84(Y1_Osc, 0, Y1_mult, 0);
AudioConnection          patchCord85(Y5_Osc, 0, Y5_Mult, 0);
AudioConnection          patchCord86(Y6_Osc, 0, Y6_Mult, 0);
AudioConnection          patchCord87(Y7_Osc, 0, Y7_Mult, 0);
AudioConnection          patchCord88(Y4_Osc, 0, Y4_mult, 0);
AudioConnection          patchCord89(Y8_Osc, 0, Y8_Mult, 0);
AudioConnection          patchCord90(B_Dc, 0, B_Mix, 0);
AudioConnection          patchCord91(Y3_Osc, 0, Y3_mult, 0);
AudioConnection          patchCord92(X1_Osc, 0, X1_mult, 0);
AudioConnection          patchCord93(X5_Osc, 0, X5_Mult, 0);
AudioConnection          patchCord94(X2_Osc, 0, X2_mult, 0);
AudioConnection          patchCord95(X6_Osc, 0, X6_Mult, 0);
AudioConnection          patchCord96(X3_Osc, 0, X3_mult, 0);
AudioConnection          patchCord97(X7_Osc, 0, X7_Mult, 0);
AudioConnection          patchCord98(X4_Osc, 0, X4_mult, 0);
AudioConnection          patchCord99(X8_Osc, 0, X8_Mult, 0);
AudioConnection          patchCord100(Y1_mult, 0, Y_Mix1, 0);
AudioConnection          patchCord101(Y2_mult, 0, Y_Mix1, 1);
AudioConnection          patchCord102(Y3_mult, 0, Y_Mix1, 2);
AudioConnection          patchCord103(Y4_mult, 0, Y_Mix1, 3);
AudioConnection          patchCord104(Y8_Mult, 0, Y_Mix2, 3);
AudioConnection          patchCord105(Y6_Mult, 0, Y_Mix2, 1);
AudioConnection          patchCord106(Y7_Mult, 0, Y_Mix2, 2);
AudioConnection          patchCord107(Y5_Mult, 0, Y_Mix2, 0);
AudioConnection          patchCord108(X1_mult, 0, X_Mix1, 0);
AudioConnection          patchCord109(X5_Mult, 0, X_Mix2, 0);
AudioConnection          patchCord110(X2_mult, 0, X_Mix1, 1);
AudioConnection          patchCord111(X3_mult, 0, X_Mix1, 2);
AudioConnection          patchCord112(X7_Mult, 0, X_Mix2, 2);
AudioConnection          patchCord113(X4_mult, 0, X_Mix1, 3);
AudioConnection          patchCord114(X8_Mult, 0, X_Mix2, 3);
AudioConnection          patchCord115(X6_Mult, 0, X_Mix2, 1);
AudioConnection          patchCord116(Z_RotWave, 0, Z_Rotate, 2);
AudioConnection          patchCord117(Y_ILDmult, 0, Z_Rotate, 1);
AudioConnection          patchCord118(Z_ILDmult, 0, X_Rotate, 1);
AudioConnection          patchCord119(X_ILDmult, 0, Z_Rotate, 0);
AudioConnection          patchCord120(I_ModDc, 0, I_ModMix, 0);
AudioConnection          patchCord121(B_Mix, 0, B_Mult, 0);
AudioConnection          patchCord122(R_Mix, 0, R_Mult, 0);
AudioConnection          patchCord123(G_Mix, 0, G_Mult, 0);
AudioConnection          patchCord124(I_Mod1, 0, I_ModMix, 1);
AudioConnection          patchCord125(I_Mod2, 0, I_ModMix, 2);
AudioConnection          patchCord126(Y_OscMrSize, 0, Y_mrModMix, 0);
AudioConnection          patchCord127(X_OscMrSize, 0, X_mrModMix, 0);
AudioConnection          patchCord128(X_RotWave, 0, X_Rotate, 2);
AudioConnection          patchCord129(Z_Rotate, 0, Y_Rotate, 0);
AudioConnection          patchCord130(Z_Rotate, 1, X_Rotate, 0);
AudioConnection          patchCord131(Y_mrMod2, 0, Y_mrModMix, 2);
AudioConnection          patchCord132(Y_mrMod1, 0, Y_mrModMix, 1);
AudioConnection          patchCord133(X_mrMod1, 0, X_mrModMix, 1);
AudioConnection          patchCord134(X_mrMod2, 0, X_mrModMix, 2);
AudioConnection          patchCord135(Y_Mix1, 0, Y_Sum, 0);
AudioConnection          patchCord136(Y_Mix2, 0, Y_Sum, 3);
AudioConnection          patchCord137(X_Mix1, 0, X_Sum, 0);
AudioConnection          patchCord138(X_Mix2, 0, X_Sum, 3);
AudioConnection          patchCord139(I_ModMix, 0, B_Mult, 1);
AudioConnection          patchCord140(I_ModMix, 0, G_Mult, 1);
AudioConnection          patchCord141(I_ModMix, 0, R_Mult, 1);
AudioConnection          patchCord142(Y_mrModMix, 0, Y_mrModMult, 1);
AudioConnection          patchCord143(X_mrModMix, 0, X_mrModMult, 0);
AudioConnection          patchCord144(mrIntenseDC, 0, B_mrMult, 0);
AudioConnection          patchCord145(mrIntenseDC, 0, G_mrMult, 0);
AudioConnection          patchCord146(mrIntenseDC, 0, R_mrMult, 0);
AudioConnection          patchCord147(Y_RotWave, 0, Y_Rotate, 2);
AudioConnection          patchCord148(X_Rotate, 0, X_mrMix, 2);
AudioConnection          patchCord149(X_Rotate, 1, Y_Rotate, 1);
AudioConnection          patchCord150(B_Mult, 0, B_mrMult, 1);
AudioConnection          patchCord151(G_Mult, 0, G_mrMult, 1);
AudioConnection          patchCord152(R_Mult, 0, R_mrMult, 1);
AudioConnection          patchCord153(Y_Sum, 0, Y_mrModMult, 0);
AudioConnection          patchCord154(X_Sum, 0, X_mrModMult, 1);
AudioConnection          patchCord155(Y_mrModMult, 0, Y_mrMix, 1);
AudioConnection          patchCord156(X_mrModMult, 0, X_mrMix, 1);
AudioConnection          patchCord157(Y_Rotate, 0, Y_mrMix, 2);
AudioConnection          patchCord158(R_mrMult, 0, tdm1, 6);
AudioConnection          patchCord159(B_mrMult, 0, tdm1, 2);
AudioConnection          patchCord160(G_mrMult, 0, tdm1, 4);
AudioConnection          patchCord161(Y_mrPos, 0, Y_mrMix, 0);
AudioConnection          patchCord162(X_mrPos, 0, X_mrMix, 0);
AudioConnection          patchCord163(Y_mrMix, 0, tdm1, 8);
AudioConnection          patchCord164(X_mrMix, 0, tdm1, 10);

AudioControlCS42448      cs42448;      //xy=1861.000015258789,729.9999809265137
AudioControlPCM3168      pcm3168;      //xy=1865.666763305664,775.6666717529297
// GUItool: end automatically generated code

//------------------------------------------------------------------------------
// Define various structures that get repeated often:
struct ModSrc {AudioSynthWaveformDc& ModDC; AudioSynthWaveform& Mod1; AudioSynthWaveform& Mod2;};
struct Modulator {ModSrc Src; AudioMixer4& Mix;};

struct axis {AudioMixer4& ModMix; AudioSynthWaveform& Osc; AudioEffectMultiply& mult; AudioMixer4& Mix; int channel;};
struct QOSC {axis X,Y; float freq, ratio;};

struct ILDA {AudioPlayILDA& ilda; const char* filePath; MemBuffer* mem; float repFreq, frequency;};
struct Rotator {AudioEffectRotator& rot; AudioSynthWaveform& Mod; float freq;};
struct Rotator3D {Rotator X,Y,Z;};
//------------------------------------------------------------------------------
// Some instances of the repeated structures:
QOSC qoscs[] = {
  {{X1_ModMix, X1_Osc, X1_mult, X_Mix1, 0}, {Y1_ModMix, Y1_Osc, Y1_mult, Y_Mix1, 0}, 0.0f, 1.0f},
  {{X2_ModMix, X2_Osc, X2_mult, X_Mix1, 1}, {Y2_ModMix, Y2_Osc, Y2_mult, Y_Mix1, 1}, 0.0f, 1.0f},
  {{X3_ModMix, X3_Osc, X3_mult, X_Mix1, 2}, {Y3_ModMix, Y3_Osc, Y3_mult, Y_Mix1, 2}, 0.0f, 1.0f},
  {{X4_ModMix, X4_Osc, X4_mult, X_Mix1, 3}, {Y4_ModMix, Y4_Osc, Y4_mult, Y_Mix1, 3}, 0.0f, 1.0f},
  {{X5_ModMix, X5_Osc, X5_Mult, X_Mix2, 0}, {Y5_ModMix, Y5_Osc, Y5_Mult, Y_Mix2, 0}, 0.0f, 1.0f},
  {{X6_ModMix, X6_Osc, X6_Mult, X_Mix2, 1}, {Y6_ModMix, Y6_Osc, Y6_Mult, Y_Mix2, 1}, 0.0f, 1.0f},
  {{X7_ModMix, X7_Osc, X7_Mult, X_Mix2, 2}, {Y7_ModMix, Y7_Osc, Y7_Mult, Y_Mix2, 2}, 0.0f, 1.0f},
  {{X8_ModMix, X8_Osc, X8_Mult, X_Mix2, 3}, {Y8_ModMix, Y8_Osc, Y8_Mult, Y_Mix2, 3}, 0.0f, 1.0f},
};

ModSrc OscMod = {OscModDc, OscMod1, OscMod2};
Modulator Rmod = {{R_Dc, R_Mod1, R_Mod2}, R_Mix},
          Gmod = {{G_Dc, G_Mod1, G_Mod2}, G_Mix},
          Bmod = {{B_Dc, B_Mod1, B_Mod2}, B_Mix},
          Imod = {{I_ModDc, I_Mod1, I_Mod2}, I_ModMix},
          XmrMod = {{X_OscMrSize, X_mrMod1, X_mrMod2}, X_mrModMix},
          YmrMod = {{Y_OscMrSize, Y_mrMod1, Y_mrMod2}, Y_mrModMix};

ILDA shape = {playILDA1};
Rotator3D rotators = {{X_Rotate,X_RotWave},{Y_Rotate,Y_RotWave},{Z_Rotate,Z_RotWave}};
//------------------------------------------------------------------------------
// Some functions to update the repeated structures:
void setModLevels(axis& axis, float dc, float mod1, float mod2)
{
  axis.ModMix.gain(0, dc);
  axis.ModMix.gain(1, mod1);
  axis.ModMix.gain(2, mod2);
}

void setQuad(QOSC& qosc, float f, int shape)
{
  qosc.X.Osc.begin(1.0f,f,           shape);
  qosc.Y.Osc.begin(1.0f,f*qosc.ratio,shape);
  qosc.X.Osc.phase( 0.0f);
  qosc.Y.Osc.phase(90.0f);
  qosc.freq = f; // save for later
}

void setGain(QOSC& qosc, float level)
{
  qosc.X.Mix.gain(qosc.X.channel, level);
  qosc.Y.Mix.gain(qosc.Y.channel, level);
}

void setRatio(QOSC& qosc, float ratio)
{
  qosc.ratio = ratio;
  qosc.Y.Osc.frequency(qosc.freq*ratio);
}


void loadILDA(ILDA& ilda, const char* fp)
{
  ilda.filePath = fp;
  ilda.mem = AudioPlayILDA::loadFile(fp,MemBuffer::inExt);
  if (nullptr != ilda.mem) // load was successful
  {
    ilda.repFreq = AudioPlayILDA::repeatFrequency(ilda.mem->buffer); // natural repeat frequency
  }
}

void playILDA(ILDA& ilda, float freq)
{
  float pbr = freq / ilda.repFreq;
  ilda.ilda.setPlaybackRate(pbr);
  ilda.frequency = freq;
  ilda.ilda.play(ilda.mem->buffer, ilda.mem->bufSize);
}

void rotate(Rotator& rot, float freq)
{
  rot.freq = freq;
  if (freq > 0.0f)
    rot.Mod.begin(1.0f,freq,WAVEFORM_SAWTOOTH);
  else    
    rot.Mod.begin(1.0f,-freq,WAVEFORM_SAWTOOTH_REVERSE);
}

//------------------------------------------------------------------------------
#define PCM3168_RST 17
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void setup() 
{
  AudioMemory(100); // plenty, for queues and TDM

  pinMode(LED_BUILTIN,OUTPUT);
  pcm3168.reset(PCM3168_RST);
  
  while(!Serial)
  {
    delay(100);
    digitalToggleFast(LED_BUILTIN);
  }
    

  pcm3168.enable();
  pcm3168.volume(0.5f);
  pcm3168.inputLevel(0.5f);

  while (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("SD.begin() failed!");
    delay(500);
  }  
  
  Serial.println("=======================");
  delay(100);

  // set basic pass-through "modulation"
  OscMod.ModDC.amplitude(1.0f);
  X_OscMrSize.amplitude(1.0f);
  Y_OscMrSize.amplitude(1.0f);

  // get the ILDA object ready
  loadILDA(shape,"/ilda/triangle.ild");
  Serial.printf("%s natively runs at %.3fHz\n", shape.filePath, shape.repFreq);

  // make a triangle of rotating ellipses
  setQuad(qoscs[0], 120.0f, WAVEFORM_SINE);
  setGain(qoscs[0], 0.2f);
  setRatio(qoscs[0],1.005f);

  //*/ Choose memory or streaming playback here!
  playILDA(shape, 37.0f); // it's a triangle, so 1/3 of ellipse freq, allow for blanking
  /*/
  playILDA1.createBuffer(16384,MemBuffer::inHeap);
  playILDA1.setPlaybackRate(0.4);
  playILDA1.play(shape.filePath);
  //*/
  ILD_Mod.begin(0.001f,0.5f,WAVEFORM_SINE);
  ILD_Mod.offset(0.6f);
  rotate(rotators.Z,0.1f); // spin the triangle!

  // make them wibble
  OscMod.Mod1.begin(1.0f, 2.0f, WAVEFORM_PULSE);
  OscMod.Mod1.pulseWidth(0.25);
  setModLevels(qoscs[0].X, 0.75f,  0.25f, 0.0f);
  setModLevels(qoscs[0].Y, 0.75f,  0.25f, 0.0f);

  // set queue running
  queue1.begin();
}


//------------------------------------------------------------------------------
volatile int16_t* data;
int count;
#define BUFLEN 50
char buf[BUFLEN+1];
int idx;

void loop() 
{
  if (queue1.available()) // triggers in sync with audio update()
  {
    data = queue1.readBuffer();
    queue1.freeBuffer();
    count--;
    if (count < 0)
    {
      digitalToggleFast(LED_BUILTIN);
      count = 200;
      Serial.printf("CPU load %.2f%%\n",AudioProcessorUsageMax());
      AudioProcessorUsageMaxReset();
    }
  }

  while (Serial.available())
  {
    char ch = Serial.read();
    if (idx < BUFLEN)
      buf[idx++] = ch;

    if ('\n' == ch)
    {
      buf[idx-1]= 0; // terminate

      // interpret message here
      
      idx=0;
    }
  }
}
