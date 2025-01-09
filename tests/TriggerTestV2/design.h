#include <Audio.h>

// LaserTriggerTest: begin automatically generated code
// the following JSON string contains the whole project, 
// it's included in all generated files.
// JSON string:[{"type":"settings","data":{"main":{},"arduino":{"useExportDialog":true,"ProjectName":"LaserTriggerTest","StandardIncludeHeader":"#include <Audio.h>\n","Board":{"Platform":"","Board":"","Options":""}},"BiDirDataWebSocketBridge":{},"workspaces":{},"sidebar":{},"palette":{},"editor":{},"devTest":{},"IndexedDBfiles":{"testFileNames":"testFile.txt"},"NodeDefGenerator":{},"NodeDefManager":{},"NodeHelpManager":{},"OSC":{}}},{"type":"tab","id":"20240821T162752_605Z_e91e","label":"Modulator","nodes":[],"links":[],"export":true,"isMain":false,"mainNameType":"tabName","mainNameExt":".ino","isAudioMain":false,"generateCppDestructor":false,"extraClassDeclarations":"","settings":{},"tabOutputs":[],"tabInputs":[]},{"type":"tab","id":"20240821T164104_797Z_1546","label":"Colour","nodes":[],"links":[],"export":true,"isMain":false,"mainNameType":"tabName","mainNameExt":".ino","isAudioMain":false,"generateCppDestructor":false,"extraClassDeclarations":"","settings":{},"tabOutputs":[],"tabInputs":[]},{"type":"tab","id":"20240821T165832_452Z_660b","label":"ILDAxyzMod","nodes":[],"links":[],"export":true,"isMain":false,"mainNameType":"tabName","mainNameExt":".ino","isAudioMain":false,"generateCppDestructor":false,"extraClassDeclarations":"","settings":{},"tabOutputs":[],"tabInputs":[]},{"type":"tab","id":"20240821T163538_242Z_7a83","label":"Rotator","nodes":[],"links":[],"export":true,"isMain":false,"mainNameType":"tabName","mainNameExt":".ino","isAudioMain":false,"generateCppDestructor":false,"extraClassDeclarations":"","settings":{},"tabOutputs":[],"tabInputs":[]},{"type":"tab","id":"20240821T161559_477Z_7c72","label":"OscAxis","nodes":[],"links":[],"export":true,"isMain":false,"mainNameType":"tabName","mainNameExt":".ino","isAudioMain":false,"generateCppDestructor":false,"extraClassDeclarations":"","settings":{},"tabOutputs":[],"tabInputs":[]},{"type":"tab","id":"20240821T161757_468Z_56ab","label":"QOSC","nodes":[],"links":[],"export":true,"isMain":false,"mainNameType":"tabName","mainNameExt":".ino","isAudioMain":false,"generateCppDestructor":false,"extraClassDeclarations":"","settings":{},"tabOutputs":[],"tabInputs":[]},{"type":"tab","id":"20240821T194858_662Z_1195","label":"ILDA","nodes":[],"links":[],"export":true,"isMain":false,"mainNameType":"tabName","mainNameExt":".ino","isAudioMain":false,"generateCppDestructor":false,"extraClassDeclarations":"","settings":{},"tabOutputs":[],"tabInputs":[]},{"type":"tab","id":"20250108T143835_405Z_9a4e","label":"ILDAchannel","nodes":[],"links":[],"export":true,"isMain":false,"mainNameType":"tabName","mainNameExt":".ino","isAudioMain":false,"generateCppDestructor":false,"extraClassDeclarations":"","settings":{},"tabOutputs":[],"tabInputs":[]},{"type":"tab","id":"20240821T161510_686Z_8293","label":"Projector","nodes":[],"links":[],"export":true,"isMain":false,"mainNameType":"tabName","mainNameExt":".ino","isAudioMain":false,"generateCppDestructor":false,"extraClassDeclarations":"","settings":{"scaleFactor":0.9},"tabOutputs":[],"tabInputs":[]},{"id":"20240821T162923_118Z_ebdf","type":"TabInput","name":"src","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":120,"y":120,"z":"20240821T162752_605Z_e91e","bgColor":"#CCE6FF","wires":[["20240821T162956_003Z_2ef2:1"]]},{"id":"20240821T162938_760Z_ddf8","type":"TabOutput","name":"Out","comment":"","anchor":"","locked":false,"inputs":1,"isBus":false,"portNames":"","x":575,"y":220,"z":"20240821T162752_605Z_e91e","bgColor":"#cce6ff","wires":[]},{"id":"20240821T164955_744Z_aa44","type":"TabOutput","name":"modulation","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":510,"y":270,"z":"20240821T162752_605Z_e91e","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T163857_678Z_a86b","type":"TabInput","name":"extra_mod","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":155,"y":295,"z":"20240821T162752_605Z_e91e","bgColor":"#CCE6FF","wires":[["20240821T162827_798Z_70c8:3"]]},{"id":"20240821T162847_577Z_735e","type":"AudioSynthWaveformDc","name":"DC","comment":"","anchor":"0","locked":false,"arraySize":1,"x":124,"y":180,"z":"20240821T162752_605Z_e91e","bgColor":"#E6E0F8","wires":[["20240821T162827_798Z_70c8:0"]]},{"id":"20240821T162847_578Z_61a5","type":"AudioSynthWaveform","name":"Mod1","comment":"","anchor":"0","locked":false,"arraySize":1,"x":127,"y":216,"z":"20240821T162752_605Z_e91e","bgColor":"#E6E0F8","wires":[["20240821T162827_798Z_70c8:1"]]},{"id":"20240821T162847_578Z_7b5","type":"AudioSynthWaveform","name":"Mod2","comment":"","anchor":"0","locked":false,"arraySize":1,"x":126,"y":252,"z":"20240821T162752_605Z_e91e","bgColor":"#E6E0F8","wires":[["20240821T162827_798Z_70c8:2"]]},{"id":"20240821T162827_798Z_70c8","type":"AudioMixer4","name":"Mix","comment":"","anchor":"0","locked":false,"arraySize":1,"x":315,"y":245,"z":"20240821T162752_605Z_e91e","bgColor":"#E6E0F8","wires":[["20240821T164955_744Z_aa44:0","20240821T162956_003Z_2ef2:0"]]},{"id":"20240821T162956_003Z_2ef2","type":"AudioEffectMultiply","name":"mult","comment":"","anchor":"0","locked":false,"arraySize":1,"x":460,"y":220,"z":"20240821T162752_605Z_e91e","bgColor":"#E6E0F8","wires":[["20240821T162938_760Z_ddf8:0"]]},{"id":"20240821T164422_052Z_4ebb","type":"TabInput","name":"intensity","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":300,"y":195,"z":"20240821T164104_797Z_1546","bgColor":"#CCE6FF","wires":[["20240821T164119_897Z_c468:0"]]},{"id":"20240821T164234_244Z_e084","type":"TabOutput","name":"Out","comment":"","anchor":"","locked":false,"inputs":1,"isBus":false,"portNames":"","x":805,"y":240,"z":"20240821T164104_797Z_1546","bgColor":"#cce6ff","wires":[]},{"id":"20240821T164304_140Z_1841","type":"TabInput","name":"ilda","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":295,"y":255,"z":"20240821T164104_797Z_1546","bgColor":"#CCE6FF","wires":[["20240821T164119_897Z_c468:1"]]},{"id":"20240821T164242_328Z_1417","type":"TabInput","name":"master","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":455,"y":290,"z":"20240821T164104_797Z_1546","bgColor":"#CCE6FF","wires":[["20240821T164211_444Z_d264:1"]]},{"id":"20240821T164119_897Z_c468","type":"Modulator","name":"modulator","comment":"","anchor":"","locked":false,"arraySize":1,"x":454.28571428571433,"y":222.85714285714286,"z":"20240821T164104_797Z_1546","bgColor":"#ccffcc","wires":[["20240821T164211_444Z_d264:0"],[]]},{"id":"20240821T164211_444Z_d264","type":"AudioEffectMultiply","name":"mult","comment":"","anchor":"0","locked":false,"arraySize":1,"x":645,"y":240,"z":"20240821T164104_797Z_1546","bgColor":"#E6E0F8","wires":[["20240821T164234_244Z_e084:0"]]},{"id":"20240821T165934_243Z_6500","type":"TabOutput","name":"Xout","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":680,"y":160,"z":"20240821T165832_452Z_660b","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T165934_242Z_63e8","type":"TabInput","name":"Xin","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":335,"y":160,"z":"20240821T165832_452Z_660b","bgColor":"#CCE6FF","wires":[["20240821T165851_823Z_b21e:0"]]},{"id":"20240821T165934_244Z_69a8","type":"TabInput","name":"Yin","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":333,"y":201,"z":"20240821T165832_452Z_660b","bgColor":"#CCE6FF","wires":[["20240821T165851_824Z_a80:0"]]},{"id":"20240821T165934_245Z_2cb8","type":"TabOutput","name":"Yout","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":677,"y":208,"z":"20240821T165832_452Z_660b","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T170021_500Z_6d87","type":"TabInput","name":"Zin","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":336,"y":243,"z":"20240821T165832_452Z_660b","bgColor":"#CCE6FF","wires":[["20240821T165851_824Z_4619:0"]]},{"id":"20240821T170021_499Z_f38","type":"TabOutput","name":"Zout","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":680,"y":250,"z":"20240821T165832_452Z_660b","bgColor":"#CCE6FF","wires":[]},{"id":"20250108T143211_745Z_1c16","type":"TabInput","name":"ModMult","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":170,"y":345,"z":"20240821T165832_452Z_660b","bgColor":"#CCE6FF","wires":[["20250108T143057_097Z_f099:1"]]},{"id":"20240821T165851_822Z_49a5","type":"AudioSynthWaveform","name":"Mod","comment":"","anchor":"0","locked":false,"arraySize":1,"x":170,"y":265,"z":"20240821T165832_452Z_660b","bgColor":"#E6E0F8","wires":[["20250108T143057_097Z_f099:0"]]},{"id":"20250108T143057_097Z_f099","type":"AudioEffectMultiply","name":"ModMult","comment":"","anchor":"0","locked":false,"arraySize":1,"x":320,"y":310,"z":"20240821T165832_452Z_660b","bgColor":"#E6E0F8","wires":[["20240821T165851_823Z_b21e:1","20240821T165851_824Z_a80:1","20240821T165851_824Z_4619:1"]]},{"id":"20240821T165851_823Z_b21e","type":"AudioEffectMultiply","name":"X_ILDmult","locked":false,"arraySize":1,"x":505,"y":170,"z":"20240821T165832_452Z_660b","bgColor":"#E6E0F8","wires":[["20240821T165934_243Z_6500:0"]]},{"id":"20240821T165851_824Z_a80","type":"AudioEffectMultiply","name":"Y_ILDmult","locked":false,"arraySize":1,"x":504,"y":206,"z":"20240821T165832_452Z_660b","bgColor":"#E6E0F8","wires":[["20240821T165934_245Z_2cb8:0"]]},{"id":"20240821T165851_824Z_4619","type":"AudioEffectMultiply","name":"Z_ILDmult","locked":false,"arraySize":1,"x":504,"y":241,"z":"20240821T165832_452Z_660b","bgColor":"#E6E0F8","wires":[["20240821T170021_499Z_f38:0"]]},{"id":"20240821T163645_121Z_8a5d","type":"TabInput","name":"Xin","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":315,"y":165,"z":"20240821T163538_242Z_7a83","bgColor":"#CCE6FF","wires":[["20240821T163600_445Z_934b:0"]]},{"id":"20240821T163732_690Z_5085","type":"TabOutput","name":"Xout","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":648,"y":177,"z":"20240821T163538_242Z_7a83","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T163658_132Z_4024","type":"TabInput","name":"Yin","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":313,"y":206,"z":"20240821T163538_242Z_7a83","bgColor":"#CCE6FF","wires":[["20240821T163600_445Z_934b:1"]]},{"id":"20240821T163747_445Z_7390","type":"TabOutput","name":"Yout","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":645,"y":225,"z":"20240821T163538_242Z_7a83","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T163600_445Z_b897","type":"AudioSynthWaveform","name":"Mod","comment":"","anchor":"0","locked":false,"arraySize":1,"x":315,"y":260,"z":"20240821T163538_242Z_7a83","bgColor":"#E6E0F8","wires":[["20240821T163600_445Z_934b:2"]]},{"id":"20240821T163600_445Z_934b","type":"AudioEffectRotator","name":"Rotate","comment":"","x":499,"y":201,"z":"20240821T163538_242Z_7a83","bgColor":"#FFEEEE","wires":[["20240821T163732_690Z_5085:0"],["20240821T163747_445Z_7390:0"]]},{"id":"20240821T200246_355Z_9d39","type":"Function","name":"code","comment":"void rotate(float _freq)\r\n{\r\n  freq = _freq;\r\n  if (freq > 0.0f)\r\n    Mod.begin(1.0f,freq,WAVEFORM_SAWTOOTH);\r\n  else    \r\n    Mod.begin(1.0f,-freq,WAVEFORM_SAWTOOTH_REVERSE);\r\n}","anchor":"0","locked":false,"x":450,"y":305,"z":"20240821T163538_242Z_7a83","bgColor":"#DDFFBB","wires":[]},{"id":"20240821T200431_256Z_566d","type":"Variables","name":"vars","comment":"float freq;","anchor":"0","locked":false,"x":555,"y":305,"z":"20240821T163538_242Z_7a83","bgColor":"#DDFFBB","wires":[]},{"id":"20240821T161646_644Z_beba","type":"TabInput","name":"DC","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":167,"y":127,"z":"20240821T161559_477Z_7c72","bgColor":"#CCE6FF","wires":[["20240821T161609_455Z_426:0"]]},{"id":"20240821T161732_383Z_218","type":"TabOutput","name":"Out","comment":"","anchor":"","locked":false,"inputs":1,"isBus":false,"portNames":"","x":640,"y":150,"z":"20240821T161559_477Z_7c72","bgColor":"#cce6ff","wires":[]},{"id":"20240821T161656_446Z_5862","type":"TabInput","name":"Mod1","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":175,"y":170,"z":"20240821T161559_477Z_7c72","bgColor":"#CCE6FF","wires":[["20240821T161609_455Z_426:1"]]},{"id":"20240821T161710_364Z_6a6e","type":"TabInput","name":"Mod2","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":175,"y":210,"z":"20240821T161559_477Z_7c72","bgColor":"#CCE6FF","wires":[["20240821T161609_455Z_426:2"]]},{"id":"20240821T161609_455Z_a277","type":"AudioSynthWaveform","name":"Osc","comment":"","anchor":"0","locked":false,"arraySize":1,"x":370,"y":115,"z":"20240821T161559_477Z_7c72","bgColor":"#E6E0F8","wires":[["20240821T161609_456Z_9699:0"]]},{"id":"20240821T161609_455Z_426","type":"AudioMixer4","name":"ModMix","comment":"","anchor":"0","locked":false,"arraySize":1,"x":355,"y":175,"z":"20240821T161559_477Z_7c72","bgColor":"#E6E0F8","wires":[["20240821T161609_456Z_9699:1"]]},{"id":"20240821T193644_126Z_b938","type":"Function","name":"code","comment":"void setModLevels(float dc, float mod1, float mod2)\r\n{\r\n  ModMix.gain(0, dc);\r\n  ModMix.gain(1, mod1);\r\n  ModMix.gain(2, mod2);\r\n}","anchor":"0","locked":false,"x":375,"y":270,"z":"20240821T161559_477Z_7c72","bgColor":"#DDFFBB","wires":[]},{"id":"20240821T161609_456Z_9699","type":"AudioEffectMultiply","name":"mult","comment":"","anchor":"0","locked":false,"arraySize":1,"x":525,"y":150,"z":"20240821T161559_477Z_7c72","bgColor":"#E6E0F8","wires":[["20240821T161732_383Z_218:0"]]},{"id":"20240821T161857_548Z_51f9","type":"TabInput","name":"DC","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":140,"y":70,"z":"20240821T161757_468Z_56ab","bgColor":"#CCE6FF","wires":[["20240821T161813_247Z_e26d:0","20240821T161816_772Z_9eda:0"]]},{"id":"20240821T161950_004Z_ad36","type":"TabOutput","name":"OutX","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":425,"y":85,"z":"20240821T161757_468Z_56ab","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T161857_549Z_3c0e","type":"TabInput","name":"Mod1","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":148,"y":113,"z":"20240821T161757_468Z_56ab","bgColor":"#CCE6FF","wires":[["20240821T161813_247Z_e26d:1","20240821T161816_772Z_9eda:1"]]},{"id":"20240821T162000_622Z_6a81","type":"TabOutput","name":"OutY","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":425,"y":135,"z":"20240821T161757_468Z_56ab","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T161857_550Z_e4ad","type":"TabInput","name":"Mod2","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":148,"y":153,"z":"20240821T161757_468Z_56ab","bgColor":"#CCE6FF","wires":[["20240821T161813_247Z_e26d:2","20240821T161816_772Z_9eda:2"]]},{"id":"20240821T195945_837Z_68ae","type":"ConstructorCode","name":"constructor code","comment":"ratio = 1.0f;","anchor":"0","locked":false,"x":159,"y":261,"z":"20240821T161757_468Z_56ab","bgColor":"#DDFFBB","wires":[]},{"id":"20240821T161813_247Z_e26d","type":"OscAxis","name":"X","comment":"","anchor":"0","locked":false,"arraySize":1,"x":303,"y":84,"z":"20240821T161757_468Z_56ab","bgColor":"#CCFFCC","wires":[["20240821T161950_004Z_ad36:0"]]},{"id":"20240821T161816_772Z_9eda","type":"OscAxis","name":"Y","comment":"","anchor":"0","locked":false,"arraySize":1,"x":302,"y":143,"z":"20240821T161757_468Z_56ab","bgColor":"#CCFFCC","wires":[["20240821T162000_622Z_6a81:0"]]},{"id":"20240821T195834_164Z_8497","type":"Variables","name":"vars","comment":"float freq, ratio;","anchor":"0","locked":false,"x":304,"y":272,"z":"20240821T161757_468Z_56ab","bgColor":"#DDFFBB","wires":[]},{"id":"20240821T193823_943Z_290c","type":"Function","name":"code","comment":"void setQuad(float f, int shape)\r\n{\r\n  X.Osc.begin(1.0f,f,shape);\r\n  Y.Osc.begin(1.0f,f*ratio,shape);\r\n  X.Osc.phase( 0.0f);\r\n  Y.Osc.phase(90.0f);\r\n  freq = f; // save for later\r\n}\r\n\r\nvoid setRatio(float _ratio)\r\n{\r\n  ratio = ratio;\r\n  Y.Osc.frequency(freq*ratio);\r\n}","anchor":"0","locked":false,"x":420,"y":275,"z":"20240821T161757_468Z_56ab","bgColor":"#DDFFBB","wires":[]},{"id":"20240821T194959_491Z_87e7","type":"TabOutput","name":"X","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":445,"y":85,"z":"20240821T194858_662Z_1195","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T194959_492Z_cf33","type":"TabOutput","name":"Y","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":447,"y":118,"z":"20240821T194858_662Z_1195","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T194959_492Z_e989","type":"TabOutput","name":"Z","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":445,"y":155,"z":"20240821T194858_662Z_1195","bgColor":"#CCE6FF","wires":[]},{"id":"20250108T142836_468Z_52ea","type":"TabInput","name":"trigger","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":140,"y":165,"z":"20240821T194858_662Z_1195","bgColor":"#CCE6FF","wires":[["20240821T194919_503Z_aad0:0"]]},{"id":"20240821T195109_079Z_b62e","type":"TabOutput","name":"R","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":450,"y":195,"z":"20240821T194858_662Z_1195","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T195109_079Z_e56b","type":"TabOutput","name":"G","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":452,"y":228,"z":"20240821T194858_662Z_1195","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T195109_080Z_487e","type":"TabOutput","name":"B","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":450,"y":265,"z":"20240821T194858_662Z_1195","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T194934_165Z_ac83","type":"TabOutput","name":"blank","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":440,"y":320,"z":"20240821T194858_662Z_1195","bgColor":"#CCE6FF","wires":[]},{"id":"20240821T194919_503Z_aad0","type":"AudioPlayILDA","name":"playILDA","comment":"","x":285,"y":165,"z":"20240821T194858_662Z_1195","bgColor":"#FFEEEE","wires":[["20240821T194959_491Z_87e7:0"],["20240821T194959_492Z_cf33:0"],["20240821T194959_492Z_e989:0"],["20240821T195109_079Z_b62e:0"],["20240821T195109_079Z_e56b:0"],["20240821T195109_080Z_487e:0"],["20240821T194934_165Z_ac83:0"]]},{"id":"20240821T195244_639Z_c29e","type":"Variables","name":"vars","comment":"const char* filePath; \nMemBuffer* mem; \nfloat repFreq, frequency;","anchor":"0","locked":false,"x":444,"y":411,"z":"20240821T194858_662Z_1195","bgColor":"#DDFFBB","wires":[]},{"id":"20240821T195448_648Z_e6ab","type":"Function","name":"code","comment":"void load(const char* fp)\r\n{\r\n  filePath = fp;\r\n  mem = AudioPlayILDA::loadFile(fp,MemBuffer::inExt);\r\n  if (nullptr != mem) // load was successful\r\n  {\r\n    repFreq = AudioPlayILDA::repeatFrequency(mem->buffer); // natural repeat frequency\r\n  }\r\n}\r\n\r\nvoid play(float freq)\r\n{\r\n  float pbr = freq / repFreq;\r\n  playILDA.setPlaybackRate(pbr);\r\n  frequency = freq;\r\n  playILDA.play(mem->buffer, mem->bufSize);\r\n}","anchor":"0","locked":false,"x":550,"y":415,"z":"20240821T194858_662Z_1195","bgColor":"#DDFFBB","wires":[]},{"id":"20250108T160030_447Z_cea8","type":"TabOutput","name":"X","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":1030,"y":95,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCE6FF","wires":[]},{"id":"20250108T160030_448Z_ca85","type":"TabOutput","name":"Y","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":1030,"y":135,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCE6FF","wires":[]},{"id":"20250108T155919_700Z_33c1","type":"TabInput","name":"trigger","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":125,"y":140,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCE6FF","wires":[["20250108T143919_012Z_c288:0"]]},{"id":"20250108T160030_448Z_c00","type":"TabOutput","name":"Z","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":1030,"y":180,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCE6FF","wires":[]},{"id":"20250108T155945_621Z_6ae3","type":"TabInput","name":"ModMult","comment":"","anchor":"0","locked":false,"outputs":1,"isBus":false,"portNames":"","x":135,"y":250,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCE6FF","wires":[["20250108T143919_013Z_c73f:3"]]},{"id":"20250108T160030_449Z_d78a","type":"TabOutput","name":"R","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":1015,"y":260,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCE6FF","wires":[]},{"id":"20250108T160030_449Z_e2b5","type":"TabOutput","name":"G","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":1017,"y":293,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCE6FF","wires":[]},{"id":"20250108T160030_449Z_6e5c","type":"TabOutput","name":"B","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":1015,"y":330,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCE6FF","wires":[]},{"id":"20250108T160030_449Z_9f65","type":"TabOutput","name":"blank","comment":"","anchor":"0","locked":false,"inputs":1,"isBus":false,"portNames":"","x":1005,"y":385,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCE6FF","wires":[]},{"id":"20250108T143919_012Z_c288","type":"ILDA","name":"ilda","comment":"","anchor":"0","locked":false,"arraySize":1,"x":255,"y":140,"z":"20250108T143835_405Z_9a4e","bgColor":"#FFEEEE","wires":[["20250108T143919_013Z_c73f:0"],["20250108T143919_013Z_c73f:1"],["20250108T143919_013Z_c73f:2"],["20250108T160030_449Z_d78a:0"],["20250108T160030_449Z_e2b5:0"],["20250108T160030_449Z_6e5c:0"],["20250108T160030_449Z_9f65:0"]]},{"id":"20250108T143919_013Z_c73f","type":"ILDAxyzMod","name":"ildaxyzmod","comment":"","anchor":"","locked":false,"arraySize":1,"x":465,"y":115,"z":"20250108T143835_405Z_9a4e","bgColor":"#ccffcc","wires":[["20250108T143919_014Z_1234:0"],["20250108T143919_014Z_1234:1"],["20250108T143919_015Z_a3a9:1"]]},{"id":"20250108T143919_014Z_1234","type":"Rotator","name":"rotatorZ","comment":"","anchor":"0","locked":false,"arraySize":1,"x":620,"y":100,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCFFCC","wires":[["20250108T143919_015Z_4b47:0"],["20250108T143919_015Z_a3a9:0"]]},{"id":"20250108T143919_015Z_a3a9","type":"Rotator","name":"rotatorX","comment":"","anchor":"0","locked":false,"arraySize":1,"x":760,"y":120,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCFFCC","wires":[["20250108T160030_448Z_ca85:0","20250108T143919_015Z_4b47:1"],["20250108T160030_448Z_c00:0"]]},{"id":"20250108T143919_015Z_4b47","type":"Rotator","name":"rotatorY","comment":"","anchor":"0","locked":false,"arraySize":1,"x":905,"y":100,"z":"20250108T143835_405Z_9a4e","bgColor":"#CCFFCC","wires":[["20250108T160030_447Z_cea8:0"],[]]},{"id":"20250108T161414_135Z_f1a5","type":"AudioSynthWaveform","name":"trig1","comment":"","anchor":"0","locked":false,"arraySize":1,"x":120,"y":292.22222222222223,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20250108T160441_713Z_8c58:0","20250108T160441_713Z_8c58:1","20240821T170511_388Z_1209:2","20240821T170511_386Z_5fbe:2","20240821T163323_774Z_4fb4:12"]]},{"id":"20250108T161444_068Z_e73a","type":"AudioSynthWaveform","name":"trig2","comment":"","anchor":"0","locked":false,"arraySize":1,"x":160,"y":445,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20250108T161250_336Z_3dd:0","20250108T161250_336Z_3dd:1","20240821T170511_388Z_1209:3","20240821T170511_386Z_5fbe:3","20240821T163323_774Z_4fb4:14"]]},{"id":"20250108T160441_713Z_8c58","type":"ILDAchannel","name":"ildachannel1","comment":"","anchor":"0","locked":false,"arraySize":1,"x":425,"y":310,"z":"20240821T161510_686Z_8293","bgColor":"#CCFFCC","wires":[["20250108T160839_861Z_4c51:0"],["20250108T161024_931Z_8bfa:0"],[],["20250108T161026_913Z_fab4:0"],["20250108T161028_169Z_bdb9:0"],["20250108T161030_065Z_5520:0"],[]]},{"id":"20250108T161250_336Z_3dd","type":"ILDAchannel","name":"ildachannel2","comment":"","anchor":"0","locked":false,"arraySize":1,"x":435,"y":455,"z":"20240821T161510_686Z_8293","bgColor":"#CCFFCC","wires":[["20250108T160839_861Z_4c51:1"],["20250108T161024_931Z_8bfa:1"],[],["20250108T161026_913Z_fab4:1"],["20250108T161028_169Z_bdb9:1"],["20250108T161030_065Z_5520:1"],[]]},{"id":"20240821T194232_689Z_8e2d","type":"Function","name":"code","comment":"/*\r\nvoid setQOSClevel(int channel, float level)\r\n{\r\n  mixerX.gain(channel, level);\r\n  mixerY.gain(channel, level);\r\n}\r\n*/\r\n","anchor":"0","locked":false,"x":685.5555555555555,"y":665,"z":"20240821T161510_686Z_8293","bgColor":"#DDFFBB","wires":[]},{"id":"20250108T160839_861Z_4c51","type":"AudioMixer4","name":"ILDAmixerX","comment":"","anchor":"0","locked":false,"arraySize":1,"x":719,"y":207,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20240821T170511_388Z_1209:1"]]},{"id":"20250108T161024_931Z_8bfa","type":"AudioMixer4","name":"ILDAmixerY","comment":"","anchor":"0","locked":false,"arraySize":1,"x":725,"y":280,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20240821T170511_386Z_5fbe:1"]]},{"id":"20250108T161026_913Z_fab4","type":"AudioMixer4","name":"ILDAmixerR","comment":"","anchor":"0","locked":false,"arraySize":1,"x":725,"y":365,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20240821T164852_517Z_55d3:1"]]},{"id":"20250108T161028_169Z_bdb9","type":"AudioMixer4","name":"ILDAmixerG","comment":"","anchor":"0","locked":false,"arraySize":1,"x":725,"y":430,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20240821T165041_367Z_f93d:1"]]},{"id":"20250108T161030_065Z_5520","type":"AudioMixer4","name":"ILDAmixerB","comment":"","anchor":"0","locked":false,"arraySize":1,"x":725,"y":500,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20240821T165042_170Z_fa19:1"]]},{"id":"20250108T161940_242Z_3ffc","type":"ConstructorCode","name":"constructor code","comment":"MrIntense.amplitude(1.0f);","anchor":"0","locked":false,"x":728.8888888888889,"y":724.4444444444445,"z":"20240821T161510_686Z_8293","bgColor":"#DDFFBB","wires":[]},{"id":"20240821T165029_662Z_97f2","type":"Modulator","name":"intensity","comment":"","anchor":"0","locked":false,"arraySize":1,"x":910,"y":405,"z":"20240821T161510_686Z_8293","bgColor":"#CCFFCC","wires":[[],["20240821T164852_517Z_55d3:0","20240821T165041_367Z_f93d:0","20240821T165042_170Z_fa19:0"]]},{"id":"20240821T165453_251Z_bafe","type":"AudioSynthWaveformDc","name":"MrIntense","comment":"","anchor":"0","locked":false,"arraySize":1,"x":915,"y":465,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20240821T164852_517Z_55d3:2","20240821T165041_367Z_f93d:2","20240821T165042_170Z_fa19:2"]]},{"id":"20240821T170511_384Z_a339","type":"AudioSynthWaveformDc","name":"X_mrPos","locked":false,"arraySize":1,"x":1015,"y":130,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20240821T170511_388Z_1209:0"]]},{"id":"20240821T170511_381Z_e4e6","type":"AudioSynthWaveformDc","name":"Y_mrPos","locked":false,"arraySize":1,"x":1025,"y":250,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20240821T170511_386Z_5fbe:0"]]},{"id":"20240821T170511_388Z_1209","type":"AudioMixer4","name":"X_mrMix","locked":false,"arraySize":1,"x":1157,"y":201,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20240822T183902_057Z_1849:0","20240821T163323_774Z_4fb4:0"]]},{"id":"20240821T170511_386Z_5fbe","type":"AudioMixer4","name":"Y_mrMix","locked":false,"arraySize":1,"x":1160,"y":295,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[["20240821T163323_774Z_4fb4:2"]]},{"id":"20240821T164852_517Z_55d3","type":"Colour","name":"R","comment":"","anchor":"0","locked":false,"arraySize":1,"x":1150,"y":385,"z":"20240821T161510_686Z_8293","bgColor":"#F86236","wires":[["20240821T163323_774Z_4fb4:4"]]},{"id":"20240821T165041_367Z_f93d","type":"Colour","name":"G","comment":"","anchor":"0","locked":false,"arraySize":1,"x":1150,"y":440,"z":"20240821T161510_686Z_8293","bgColor":"#46D75E","wires":[["20240821T163323_774Z_4fb4:6"]]},{"id":"20240821T165042_170Z_fa19","type":"Colour","name":"B","comment":"","anchor":"0","locked":false,"arraySize":1,"x":1150,"y":495,"z":"20240821T161510_686Z_8293","bgColor":"#79ACF8","wires":[["20240821T163323_774Z_4fb4:9"]]},{"id":"20240822T183902_057Z_1849","type":"AudioRecordQueue","name":"queue","comment":"","anchor":"","locked":false,"arraySize":1,"x":1282,"y":141,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[]},{"id":"20240821T163323_774Z_4fb4","type":"AudioOutputTDM","name":"tdm1","locked":false,"inputs":16,"x":1340,"y":365,"z":"20240821T161510_686Z_8293","bgColor":"#E6E0F8","wires":[]}]


class Modulator 
{
public:
    AudioSynthWaveformDc            DC;
    AudioSynthWaveform              Mod1;
    AudioSynthWaveform              Mod2;
    AudioMixer4                     Mix;
    AudioEffectMultiply             mult;
    AudioConnection                  *patchCord[4]; // total patchCordCount:4 including array typed ones.

// constructor (this is called when class-object is created)
    Modulator() { 
        int pci = 0; // used only for adding new patchcords


        patchCord[pci++] = new AudioConnection(DC, 0, Mix, 0);
        patchCord[pci++] = new AudioConnection(Mod1, 0, Mix, 1);
        patchCord[pci++] = new AudioConnection(Mod2, 0, Mix, 2);
        patchCord[pci++] = new AudioConnection(Mix, 0, mult, 0);
        
    }
}; // end of class Modulator

class Colour 
{
public:
    Modulator                       modulator;
    AudioEffectMultiply             mult;
    AudioConnection                  *patchCord[1]; // total patchCordCount:1 including array typed ones.

// constructor (this is called when class-object is created)
    Colour() { 
        int pci = 0; // used only for adding new patchcords


        patchCord[pci++] = new AudioConnection(modulator.mult, 0, mult, 0);
        
    }
}; // end of class Colour

class ILDAxyzMod 
{
public:
    AudioSynthWaveform              Mod;
    AudioEffectMultiply             ModMult;
    AudioEffectMultiply             X_ILDmult;
    AudioEffectMultiply             Y_ILDmult;
    AudioEffectMultiply             Z_ILDmult;
    AudioConnection                  *patchCord[4]; // total patchCordCount:4 including array typed ones.

// constructor (this is called when class-object is created)
    ILDAxyzMod() { 
        int pci = 0; // used only for adding new patchcords


        patchCord[pci++] = new AudioConnection(Mod, 0, ModMult, 0);
        patchCord[pci++] = new AudioConnection(ModMult, 0, X_ILDmult, 1);
        patchCord[pci++] = new AudioConnection(ModMult, 0, Y_ILDmult, 1);
        patchCord[pci++] = new AudioConnection(ModMult, 0, Z_ILDmult, 1);
        
    }
}; // end of class ILDAxyzMod

class Rotator 
{
public:
    float freq;
    
    AudioSynthWaveform              Mod;
    AudioEffectRotator              Rotate;
    AudioConnection                  *patchCord[1]; // total patchCordCount:1 including array typed ones.

// constructor (this is called when class-object is created)
    Rotator() { 
        int pci = 0; // used only for adding new patchcords


        patchCord[pci++] = new AudioConnection(Mod, 0, Rotate, 2);
        
    }

    void rotate(float _freq)
    {
      freq = _freq;
      if (freq > 0.0f)
        Mod.begin(1.0f,freq,WAVEFORM_SAWTOOTH);
      else    
        Mod.begin(1.0f,-freq,WAVEFORM_SAWTOOTH_REVERSE);
    }
    
}; // end of class Rotator

class OscAxis 
{
public:
    AudioSynthWaveform              Osc;
    AudioMixer4                     ModMix;
    AudioEffectMultiply             mult;
    AudioConnection                  *patchCord[2]; // total patchCordCount:2 including array typed ones.

// constructor (this is called when class-object is created)
    OscAxis() { 
        int pci = 0; // used only for adding new patchcords


        patchCord[pci++] = new AudioConnection(Osc, 0, mult, 0);
        patchCord[pci++] = new AudioConnection(ModMix, 0, mult, 1);
        
    }

    void setModLevels(float dc, float mod1, float mod2)
    {
      ModMix.gain(0, dc);
      ModMix.gain(1, mod1);
      ModMix.gain(2, mod2);
    }
    
}; // end of class OscAxis

class QOSC 
{
public:
    float freq, ratio;
    
    OscAxis                         X;
    OscAxis                         Y;

// constructor (this is called when class-object is created)
    QOSC() { 


        ratio = 1.0f;
        
    }

    void setQuad(float f, int shape)
    {
      X.Osc.begin(1.0f,f,shape);
      Y.Osc.begin(1.0f,f*ratio,shape);
      X.Osc.phase( 0.0f);
      Y.Osc.phase(90.0f);
      freq = f; // save for later
    }
    
    void setRatio(float _ratio)
    {
      ratio = ratio;
      Y.Osc.frequency(freq*ratio);
    }
    
}; // end of class QOSC

class ILDA 
{
public:
    const char* filePath; 
    MemBuffer* mem; 
    float repFreq, frequency;
    
    AudioPlayILDA                   playILDA;

// constructor (this is called when class-object is created)
    ILDA() { 


        
    }

    void load(const char* fp)
    {
      filePath = fp;
      mem = AudioPlayILDA::loadFile(fp,MemBuffer::inExt);
      if (nullptr != mem) // load was successful
      {
        repFreq = AudioPlayILDA::repeatFrequency(mem->buffer); // natural repeat frequency
      }
    }
    
    void play(float freq)
    {
      float pbr = freq / repFreq;
      playILDA.setPlaybackRate(pbr);
      frequency = freq;
      playILDA.play(mem->buffer, mem->bufSize);
    }
    
}; // end of class ILDA

class ILDAchannel 
{
public:
    ILDA                            ilda;
    ILDAxyzMod                      ildaxyzmod;
    Rotator                         rotatorZ;
    Rotator                         rotatorX;
    Rotator                         rotatorY;
    AudioConnection                  *patchCord[9]; // total patchCordCount:9 including array typed ones.

// constructor (this is called when class-object is created)
    ILDAchannel() { 
        int pci = 0; // used only for adding new patchcords


        patchCord[pci++] = new AudioConnection(ilda.playILDA, 0, ildaxyzmod.X_ILDmult, 0);
        patchCord[pci++] = new AudioConnection(ilda.playILDA, 1, ildaxyzmod.Y_ILDmult, 0);
        patchCord[pci++] = new AudioConnection(ilda.playILDA, 2, ildaxyzmod.Z_ILDmult, 0);
        patchCord[pci++] = new AudioConnection(ildaxyzmod.X_ILDmult, 0, rotatorZ.Rotate, 0);
        patchCord[pci++] = new AudioConnection(ildaxyzmod.Y_ILDmult, 0, rotatorZ.Rotate, 1);
        patchCord[pci++] = new AudioConnection(ildaxyzmod.Z_ILDmult, 0, rotatorX.Rotate, 1);
        patchCord[pci++] = new AudioConnection(rotatorZ.Rotate, 0, rotatorY.Rotate, 0);
        patchCord[pci++] = new AudioConnection(rotatorZ.Rotate, 1, rotatorX.Rotate, 0);
        patchCord[pci++] = new AudioConnection(rotatorX.Rotate, 0, rotatorY.Rotate, 1);
        
    }
}; // end of class ILDAchannel

class Projector 
{
public:
    AudioSynthWaveform              trig1;
    AudioSynthWaveform              trig2;
    ILDAchannel                     ildachannel1;
    ILDAchannel                     ildachannel2;
    AudioMixer4                     ILDAmixerX;
    AudioMixer4                     ILDAmixerY;
    AudioMixer4                     ILDAmixerR;
    AudioMixer4                     ILDAmixerG;
    AudioMixer4                     ILDAmixerB;
    Modulator                       intensity;
    AudioSynthWaveformDc            MrIntense;
    AudioSynthWaveformDc            X_mrPos;
    AudioSynthWaveformDc            Y_mrPos;
    AudioMixer4                     X_mrMix;
    AudioMixer4                     Y_mrMix;
    Colour                          R;
    Colour                          G;
    Colour                          B;
    AudioRecordQueue                queue;
    AudioOutputTDM                  tdm1;
    AudioConnection                  *patchCord[39]; // total patchCordCount:39 including array typed ones.

// constructor (this is called when class-object is created)
    Projector() { 
        int pci = 0; // used only for adding new patchcords


        patchCord[pci++] = new AudioConnection(trig1, 0, ildachannel1.ilda.playILDA, 0);
        patchCord[pci++] = new AudioConnection(trig1, 0, ildachannel1.ildaxyzmod.ModMult, 1);
        patchCord[pci++] = new AudioConnection(trig1, 0, X_mrMix, 2);
        patchCord[pci++] = new AudioConnection(trig1, 0, Y_mrMix, 2);
        patchCord[pci++] = new AudioConnection(trig1, 0, tdm1, 12);
        patchCord[pci++] = new AudioConnection(trig2, 0, ildachannel2.ilda.playILDA, 0);
        patchCord[pci++] = new AudioConnection(trig2, 0, ildachannel2.ildaxyzmod.ModMult, 1);
        patchCord[pci++] = new AudioConnection(trig2, 0, X_mrMix, 3);
        patchCord[pci++] = new AudioConnection(trig2, 0, Y_mrMix, 3);
        patchCord[pci++] = new AudioConnection(trig2, 0, tdm1, 14);
        patchCord[pci++] = new AudioConnection(ildachannel1.rotatorY.Rotate, 0, ILDAmixerX, 0);
        patchCord[pci++] = new AudioConnection(ildachannel1.rotatorX.Rotate, 0, ILDAmixerY, 0);
        patchCord[pci++] = new AudioConnection(ildachannel1.ilda.playILDA, 3, ILDAmixerR, 0);
        patchCord[pci++] = new AudioConnection(ildachannel1.ilda.playILDA, 4, ILDAmixerG, 0);
        patchCord[pci++] = new AudioConnection(ildachannel1.ilda.playILDA, 5, ILDAmixerB, 0);
        patchCord[pci++] = new AudioConnection(ildachannel2.rotatorY.Rotate, 0, ILDAmixerX, 1);
        patchCord[pci++] = new AudioConnection(ildachannel2.rotatorX.Rotate, 0, ILDAmixerY, 1);
        patchCord[pci++] = new AudioConnection(ildachannel2.ilda.playILDA, 3, ILDAmixerR, 1);
        patchCord[pci++] = new AudioConnection(ildachannel2.ilda.playILDA, 4, ILDAmixerG, 1);
        patchCord[pci++] = new AudioConnection(ildachannel2.ilda.playILDA, 5, ILDAmixerB, 1);
        patchCord[pci++] = new AudioConnection(ILDAmixerX, 0, X_mrMix, 1);
        patchCord[pci++] = new AudioConnection(ILDAmixerY, 0, Y_mrMix, 1);
        patchCord[pci++] = new AudioConnection(ILDAmixerR, 0, R.modulator.Mix, 3);
        patchCord[pci++] = new AudioConnection(ILDAmixerG, 0, G.modulator.Mix, 3);
        patchCord[pci++] = new AudioConnection(ILDAmixerB, 0, B.modulator.Mix, 3);
        patchCord[pci++] = new AudioConnection(intensity.Mix, 0, R.modulator.mult, 1);
        patchCord[pci++] = new AudioConnection(intensity.Mix, 0, G.modulator.mult, 1);
        patchCord[pci++] = new AudioConnection(intensity.Mix, 0, B.modulator.mult, 1);
        patchCord[pci++] = new AudioConnection(MrIntense, 0, R.mult, 1);
        patchCord[pci++] = new AudioConnection(MrIntense, 0, G.mult, 1);
        patchCord[pci++] = new AudioConnection(MrIntense, 0, B.mult, 1);
        patchCord[pci++] = new AudioConnection(X_mrPos, 0, X_mrMix, 0);
        patchCord[pci++] = new AudioConnection(Y_mrPos, 0, Y_mrMix, 0);
        patchCord[pci++] = new AudioConnection(X_mrMix, 0, queue, 0);
        patchCord[pci++] = new AudioConnection(X_mrMix, 0, tdm1, 0);
        patchCord[pci++] = new AudioConnection(Y_mrMix, 0, tdm1, 2);
        patchCord[pci++] = new AudioConnection(R.mult, 0, tdm1, 4);
        patchCord[pci++] = new AudioConnection(G.mult, 0, tdm1, 6);
        patchCord[pci++] = new AudioConnection(B.mult, 0, tdm1, 9);
        MrIntense.amplitude(1.0f);
        
    }

    /*
    void setQOSClevel(int channel, float level)
    {
      mixerX.gain(channel, level);
      mixerY.gain(channel, level);
    }
    */
    
    
}; // end of class Projector
// LaserTriggerTest: end automatically generated code
