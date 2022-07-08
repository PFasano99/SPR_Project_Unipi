## Sequential f: 175

- Loading video Time: 6.163152 sec
- Grayscale time : 1.128196870 sec
- GaussianFilter time : 14.254963474 sec
- Comparison time : 0.825146767 sec
- Motion detected in: 11 frames out of 175
Tot seq time: 22.371661238 sec

# Number of threads 1
-------------------------------------------------------
## Threads
- Loading video Time: 6.103219650 sec
- Grayscale time threads: 1.138534817 sec
- Gaussian threads : 14.220372908 sec
- Comparison time : 0.810868706 sec
- Motion detected in: 11 frames out of 175
- Tot thread time: 22.273165995 sec

## Fast Flow
- Loading video Time: 6.019858476 sec
- Grayscale time : 1.134195967 sec
- GaussianFilter time : 14.124454640 sec
- Comparison time : 0.825600611 sec
- Motion detected in: 11 frames out of 175
- Tot FastFlow time: 22.106800513 sec

## OpenMP
- Loading video Time: 5.915230467 sec
- Grayscale time : 1.129877319 sec
- GaussianFilter time : 14.099735972 sec
- Comparison time : 0.817892085 sec
- Motion detected in: 11 frames out of 175
- Tot OpenMp time: 21.962914658 sec
----------------------------------------------------------------

# Number of threads 4
-------------------------------------------------------
## Threads
- Loading video Time: 6.005537150 sec
- Grayscale time threads: 0.514095116 sec
- Gaussian threads : 4.066586765 sec
- Comparison time : 0.808989360 sec
- Motion detected in: 11 frames out of 175
- Tot thread time: 11.395374505 sec

## Fast Flow
- Loading video Time: 5.998909920 sec
- Grayscale time : 0.510021585 sec
- GaussianFilter time : 7.218998307 sec
- Comparison time : 0.825380598 sec
- Motion detected in: 11 frames out of 175
- Tot FastFlow time: 14.555907922 sec

## OpenMP
- Loading video Time: 5.978501469 sec
- Grayscale time : 0.507964718 sec
- GaussianFilter time : 7.315202566 sec
- Comparison time : 0.848090052 sec
- Motion detected in: 11 frames out of 175
- Tot OpenMp time: 14.649959922 sec
----------------------------------------------------------------

# Number of threads 8
-------------------------------------------------------
## Threads
- Loading video Time: 6.015677912 sec
- Grayscale time threads: 0.244661550 sec
- Gaussian threads : 3.433531870 sec
- Comparison time : 0.841210992 sec
- Motion detected in: 11 frames out of 175
- Tot thread time: 10.535256837 sec

## Fast Flow
- Loading video Time: 5.997918173 sec
- Grayscale time : 0.272165593 sec
- GaussianFilter time : 3.599892639 sec
- Comparison time : 0.824139202 sec
- Motion detected in: 11 frames out of 175
- Tot FastFlow time: 10.696941437 sec

## OpenMP
- Loading video Time: 6.031258800 sec
- Grayscale time : 0.258074244 sec
- GaussianFilter time : 3.481655203 sec
- Comparison time : 0.813513836 sec
- Motion detected in: 11 frames out of 175
- Tot OpenMp time: 10.584669897 sec
----------------------------------------------------------------

# Number of threads 16
-------------------------------------------------------
## Threads
- Loading video Time: 6.047819959 sec
- Grayscale time threads: 0.165271977 sec
- Gaussian threads : 2.009240341 sec
- Comparison time : 0.834927784 sec
- Motion detected in: 11 frames out of 175
- Tot thread time: 9.057429774 sec

## Fast Flow
- Loading video Time: 6.011998545 sec
- Grayscale time : 0.145834992 sec
- GaussianFilter time : 1.841589772 sec
- Comparison time : 0.857539428 sec
- Motion detected in: 11 frames out of 175
- Tot FastFlow time: 8.859759466 sec

## OpenMP
- Loading video Time: 6.002487977 sec
- Grayscale time : 0.138409686 sec
- GaussianFilter time : 1.840984625 sec
- Comparison time : 0.819627838 sec
- Motion detected in: 11 frames out of 175
- Tot OpenMp time: 8.801683541 sec
----------------------------------------------------------------

# Number of threads 32
-------------------------------------------------------
## Threads
- Loading video Time: 6.016558630 sec
- Grayscale time threads: 0.173823775 sec
- Gaussian threads : 2.015203234 sec
- Comparison time : 0.852862649 sec
- Motion detected in: 11 frames out of 175
- Tot thread time: 9.058606301 sec

## Fast Flow
- Loading video Time: 5.995190894 sec
- Grayscale time : 0.079796208 sec
- GaussianFilter time : 1.029270535 sec
- Comparison time : 0.808035294 sec
- Motion detected in: 11 frames out of 175
- Tot FastFlow time: 7.915008352 sec

## OpenMP
- Loading video Time: 5.967065707 sec
- Grayscale time : 0.097690367 sec
- GaussianFilter time : 1.032595307 sec
- Comparison time : 0.814360010 sec
- Motion detected in: 11 frames out of 175
- Tot OpenMp time: 7.911906007 sec
----------------------------------------------------------------

Statistics for threads
## With 1 threads:
- Speedup is 1.004422148
- Scalb is 1.000000000
- Efficency is 1.004422148
- Ideal time is 22.371661238

## With 4 threads:
- Speedup is 1.963222993
- Scalb is 1.954579552
- Efficency is 0.490805748
- Ideal time is 5.592915310

## With 8 threads:
- Speedup is 2.123504114
- Scalb is 2.114155007
- Efficency is 0.265438014
- Ideal time is 2.796457655

## With 16 threads:
- Speedup is 2.469978989
- Scalb is 2.459104465
- Efficency is 0.154373687
- Ideal time is 1.398228827

## With 32 threads:
- Speedup is 2.469658190
- Scalb is 2.458785077
- Efficency is 0.077176818
- Ideal time is 0.699114414

Statistics for FF
## With 1 threads:
- Speedup is 1.011980961
- Scalb is 1.000000000
- Efficency is 1.011980961
- Ideal time is 22.371661238

## With 4 threads:
- Speedup is 1.536947153
- Scalb is 1.518751055
- Efficency is 0.384236788
- Ideal time is 5.592915310

## With 8 threads:
- Speedup is 2.091407284
- Scalb is 2.066646868
- Efficency is 0.261425911
- Ideal time is 2.796457655

## With 16 threads:
- Speedup is 2.525086750
- Scalb is 2.495191952
- Efficency is 0.157817922
- Ideal time is 1.398228827

## With 32 threads:
- Speedup is 2.826486119
- Scalb is 2.793023018
- Efficency is 0.088327691
- Ideal time is 0.699114414

Statistics for OMP
## With 1 threads:
- Speedup is 1.018610762
- Scalb is 1.000000000
- Efficency is 1.018610762
- Ideal time is 22.371661238

## With 4 threads:
- Speedup is 1.527080030
- Scalb is 1.499179163
- Efficency is 0.381770008
- Ideal time is 5.592915310

## With 8 threads:
- Speedup is 2.113590830
- Scalb is 2.074973983
- Efficency is 0.264198854
- Ideal time is 2.796457655

## With 16 threads:
- Speedup is 2.541747966
- Scalb is 2.495308375
- Efficency is 0.158859248
- Ideal time is 1.398228827

## With 32 threads:
- Speedup is 2.827594415
- Scalb is 2.775932201
- Efficency is 0.088362325
- Ideal time is 0.699114414


## Sequential of: 1771

- Loading video Time: 51.154003 sec
- Grayscale time : 5.091473687 sec
- GaussianFilter time : 62.857510286 sec
- Comparison time : 4.112532826 sec
- Motion detected in: 396 frames out of 1771
Tot seq time: 123.215991590 sec

# Number of threads 1
-------------------------------------------------------
## Threads
- Loading video Time: 51.155120252 sec
- Grayscale time threads: 5.098457013 sec
- Gaussian threads : 62.997055070 sec
- Comparison time : 4.152759348 sec
- Motion detected in: 396 frames out of 1771
- Tot thread time: 123.403805715 sec

## Fast Flow
- Loading video Time: 49.484874015 sec
- Grayscale time : 5.081524621 sec
- GaussianFilter time : 62.936061978 sec
- Comparison time : 4.121720523 sec
- Motion detected in: 396 frames out of 1771
- Tot FastFlow time: 121.627106464 sec

## OpenMP
- Loading video Time: 49.602493212 sec
- Grayscale time : 5.078980054 sec
- GaussianFilter time : 62.931916659 sec
- Comparison time : 4.179490549 sec
- Motion detected in: 396 frames out of 1771
- Tot OpenMp time: 121.793305908 sec
----------------------------------------------------------------

# Number of threads 4
-------------------------------------------------------
## Threads
- Loading video Time: 49.725216585 sec
- Grayscale time threads: 2.200191520 sec
- Gaussian threads : 16.412432740 sec
- Comparison time : 4.143143165 sec
- Motion detected in: 396 frames out of 1771
- Tot thread time: 72.481417044 sec

## Fast Flow
- Loading video Time: 49.842314889 sec
- Grayscale time : 2.308268290 sec
- GaussianFilter time : 31.879864239 sec
- Comparison time : 4.147848266 sec
- Motion detected in: 396 frames out of 1771
- Tot FastFlow time: 88.181201014 sec

## OpenMP
- Loading video Time: 49.714824999 sec
- Grayscale time : 2.270332340 sec
- GaussianFilter time : 21.438311910 sec
- Comparison time : 4.094790638 sec
- Motion detected in: 396 frames out of 1771
- Tot OpenMp time: 77.518703024 sec
----------------------------------------------------------------

# Number of threads 8
-------------------------------------------------------
## Threads
- Loading video Time: 49.743314360 sec
- Grayscale time threads: 1.148678440 sec
- Gaussian threads : 13.327875169 sec
- Comparison time : 4.077865637 sec
- Motion detected in: 396 frames out of 1771
- Tot thread time: 68.298152539 sec

## Fast Flow
- Loading video Time: 49.379543337 sec
- Grayscale time : 1.135968613 sec
- GaussianFilter time : 15.913088456 sec
- Comparison time : 4.120193491 sec
- Motion detected in: 396 frames out of 1771
- Tot FastFlow time: 70.551784836 sec

## OpenMP
- Loading video Time: 49.404287041 sec
- Grayscale time : 1.138500686 sec
- GaussianFilter time : 14.429941882 sec
- Comparison time : 4.128680351 sec
- Motion detected in: 396 frames out of 1771
- Tot OpenMp time: 69.102006707 sec
----------------------------------------------------------------

# Number of threads 16
-------------------------------------------------------
## Threads
- Loading video Time: 49.745581195 sec
- Grayscale time threads: 0.596211876 sec
- Gaussian threads : 8.285994137 sec
- Comparison time : 4.113465795 sec
- Motion detected in: 396 frames out of 1771
- Tot thread time: 62.741707639 sec

## Fast Flow
- Loading video Time: 49.714725624 sec
- Grayscale time : 0.574272076 sec
- GaussianFilter time : 8.004550185 sec
- Comparison time : 4.132154302 sec
- Motion detected in: 396 frames out of 1771
- Tot FastFlow time: 62.428660123 sec

## OpenMP
- Loading video Time: 49.665206914 sec
- Grayscale time : 0.584867078 sec
- GaussianFilter time : 7.925239022 sec
- Comparison time : 4.141359402 sec
- Motion detected in: 396 frames out of 1771
- Tot OpenMp time: 62.317306567 sec
----------------------------------------------------------------

# Number of threads 32
-------------------------------------------------------
## Threads
- Loading video Time: 49.745588496 sec
- Grayscale time threads: 0.366707984 sec
- Gaussian threads : 4.496740558 sec
- Comparison time : 4.177838439 sec
- Motion detected in: 396 frames out of 1771
- Tot thread time: 58.787281510 sec

## Fast Flow
- Loading video Time: 49.527939938 sec
- Grayscale time : 0.364255711 sec
- GaussianFilter time : 4.452719910 sec
- Comparison time : 4.102100615 sec
- Motion detected in: 396 frames out of 1771
- Tot FastFlow time: 58.450127125 sec

## OpenMP
- Loading video Time: 49.626973364 sec
- Grayscale time : 0.350760945 sec
- GaussianFilter time : 4.269296300 sec
- Comparison time : 4.060315787 sec
- Motion detected in: 396 frames out of 1771
- Tot OpenMp time: 58.307786532 sec
----------------------------------------------------------------

Statistics for threads
## With 1 threads:
- Speedup is 0.998478052
- Scalb is 1.000000000
- Efficency is 0.998478052
- Ideal time is 123.215991590

## With 4 threads:
- Speedup is 1.699966648
- Scalb is 1.702557852
- Efficency is 0.424991662
- Ideal time is 30.803997898

## With 8 threads:
- Speedup is 1.804089672
- Scalb is 1.806839587
- Efficency is 0.225511209
- Ideal time is 15.401998949

## With 16 threads:
- Speedup is 1.963860982
- Scalb is 1.966854432
- Efficency is 0.122741311
- Ideal time is 7.700999474

## With 32 threads:
- Speedup is 2.095963420
- Scalb is 2.099158229
- Efficency is 0.065498857
- Ideal time is 3.850499737

Statistics for FF
## With 1 threads:
- Speedup is 1.013063577
- Scalb is 1.000000000
- Efficency is 1.013063577
- Ideal time is 123.215991590

## With 4 threads:
- Speedup is 1.397304529
- Scalb is 1.379286118
- Efficency is 0.349326132
- Ideal time is 30.803997898

## With 8 threads:
- Speedup is 1.746461721
- Scalb is 1.723940886
- Efficency is 0.218307715
- Ideal time is 15.401998949

## With 16 threads:
- Speedup is 1.973708732
- Scalb is 1.948257519
- Efficency is 0.123356796
- Ideal time is 7.700999474

## With 32 threads:
- Speedup is 2.108053441
- Scalb is 2.080869836
- Efficency is 0.065876670
- Ideal time is 3.850499737

Statistics for OMP
## With 1 threads:
- Speedup is 1.011681148
- Scalb is 1.000000000
- Efficency is 1.011681148
- Ideal time is 123.215991590

## With 4 threads:
- Speedup is 1.589500169
- Scalb is 1.571147364
- Efficency is 0.397375042
- Ideal time is 30.803997898

## With 8 threads:
- Speedup is 1.783102944
- Scalb is 1.762514748
- Efficency is 0.222887868
- Ideal time is 15.401998949

## With 16 threads:
- Speedup is 1.977235513
- Scalb is 1.954405808
- Efficency is 0.123577220
- Ideal time is 7.700999474

## With 32 threads:
- Speedup is 2.113199607
- Scalb is 2.088800024
- Efficency is 0.066037488
- Ideal time is 3.850499737

## Sequential of: 2290

- Loading video Time: 65.999193 sec
- Grayscale time : 6.521723694 sec
- GaussianFilter time : 80.969379151 sec
- Comparison time : 4.438605117 sec
- Motion detected in: 49 frames out of 2290
Tot seq time: 157.929842419 sec

# Number of threads 1
-------------------------------------------------------
## Threads
- Loading video Time: 66.027715804 sec
- Grayscale time threads: 6.556278757 sec
- Gaussian threads : 81.364247230 sec
- Comparison time : 4.458197487 sec
- Motion detected in: 49 frames out of 2290
- Tot thread time: 158.406938019 sec

## Fast Flow
- Loading video Time: 62.979564797 sec
- Grayscale time : 6.494077720 sec
- GaussianFilter time : 80.822635026 sec
- Comparison time : 4.435780555 sec
- Motion detected in: 49 frames out of 2290
- Tot FastFlow time: 154.735015537 sec

## OpenMP
- Loading video Time: 63.044040811 sec
- Grayscale time : 6.537101456 sec

- GaussianFilter time : 82.153505844 sec
- Comparison time : 4.440267425 sec
- Motion detected in: 49 frames out of 2290
- Tot OpenMp time: 156.175418576 sec
----------------------------------------------------------------

# Number of threads 4
-------------------------------------------------------
## Threads
- Loading video Time: 63.042469244 sec
- Grayscale time threads: 2.942451230 sec
- Gaussian threads : 21.825314822 sec
- Comparison time : 4.452471009 sec
- Motion detected in: 49 frames out of 2290
- Tot thread time: 92.263266550 sec

## Fast Flow
- Loading video Time: 63.151749161 sec
- Grayscale time : 3.041324086 sec
- GaussianFilter time : 41.772597865 sec
- Comparison time : 4.498480968 sec
- Motion detected in: 49 frames out of 2290
- Tot FastFlow time: 112.467218340 sec

## OpenMP
- Loading video Time: 63.244445082 sec
- Grayscale time : 2.952078490 sec
- GaussianFilter time : 21.813933443 sec
- Comparison time : 4.538326024 sec
- Motion detected in: 49 frames out of 2290
- Tot OpenMp time: 92.549297581 sec
----------------------------------------------------------------

# Number of threads 8
-------------------------------------------------------
## Threads
- Loading video Time: 63.141137971 sec
- Grayscale time threads: 1.473343959 sec
- Gaussian threads : 20.517501600 sec
- Comparison time : 4.472745035 sec
- Motion detected in: 49 frames out of 2290
- Tot thread time: 89.605225607 sec

## Fast Flow
- Loading video Time: 63.101833949 sec
- Grayscale time : 1.500044201 sec
- GaussianFilter time : 20.556706136 sec
- Comparison time : 4.496892527 sec
- Motion detected in: 49 frames out of 2290
- Tot FastFlow time: 89.658434960 sec

## OpenMP
- Loading video Time: 63.180472652 sec
- Grayscale time : 1.513876757 sec
- GaussianFilter time : 20.646968228 sec
- Comparison time : 4.500612318 sec
- Motion detected in: 49 frames out of 2290
- Tot OpenMp time: 89.842453198 sec
----------------------------------------------------------------

# Number of threads 16
-------------------------------------------------------
## Threads
- Loading video Time: 63.206749521 sec
- Grayscale time threads: 0.739632684 sec
- Gaussian threads : 10.280947535 sec
- Comparison time : 4.455835615 sec
- Motion detected in: 49 frames out of 2290
- Tot thread time: 78.683678497 sec

## Fast Flow
- Loading video Time: 63.130635300 sec
- Grayscale time : 0.738376296 sec
- GaussianFilter time : 10.303399262 sec
- Comparison time : 4.440322444 sec
- Motion detected in: 49 frames out of 2290
- Tot FastFlow time: 78.615790855 sec

## OpenMP
- Loading video Time: 63.149569290 sec
- Grayscale time : 0.770569603 sec
- GaussianFilter time : 10.285724118 sec
- Comparison time : 4.444208039 sec
- Motion detected in: 49 frames out of 2290
- Tot OpenMp time: 78.650606394 sec
----------------------------------------------------------------

# Number of threads 32
-------------------------------------------------------
## Threads
- Loading video Time: 63.178136312 sec
- Grayscale time threads: 0.430693883 sec
- Gaussian threads : 5.843387624 sec
- Comparison time : 4.453704373 sec
- Motion detected in: 49 frames out of 2290
- Tot thread time: 73.906433234 sec

## Fast Flow
- Loading video Time: 63.137684485 sec
- Grayscale time : 0.426039235 sec
- GaussianFilter time : 5.282975951 sec
- Comparison time : 4.540593491 sec
- Motion detected in: 49 frames out of 2290
- Tot FastFlow time: 73.390318512 sec

## OpenMP
- Loading video Time: 63.100825565 sec
- Grayscale time : 0.428864113 sec
- GaussianFilter time : 5.394156135 sec
- Comparison time : 4.512781730 sec
- Motion detected in: 49 frames out of 2290
- Tot OpenMp time: 73.437136685 sec
----------------------------------------------------------------

Statistics for threads
## With 1 threads:
- Speedup is 0.996988165
- Scalb is 1.000000000
- Efficency is 0.996988165
- Ideal time is 157.929842419

## With 4 threads:
- Speedup is 1.711730446
- Scalb is 1.716901471
- Efficency is 0.427932612
- Ideal time is 39.482460605

## With 8 threads:
- Speedup is 1.762507056
- Scalb is 1.767831474
- Efficency is 0.220313382
- Ideal time is 19.741230302

## With 16 threads:
- Speedup is 2.007148693
- Scalb is 2.013212156
- Efficency is 0.125446793
- Ideal time is 9.870615151

## With 32 threads:
- Speedup is 2.136888976
- Scalb is 2.143344376
- Efficency is 0.066777780
- Ideal time is 4.935307576

Statistics for FF
## With 1 threads:
- Speedup is 1.020647084
- Scalb is 1.000000000
- Efficency is 1.020647084
- Ideal time is 157.929842419

## With 4 threads:
- Speedup is 1.404230004
- Scalb is 1.375823265
- Efficency is 0.351057501
- Ideal time is 39.482460605

## With 8 threads:
- Speedup is 1.761461066
- Scalb is 1.725827755
- Efficency is 0.220182633
- Ideal time is 19.741230302

## With 16 threads:
- Speedup is 2.008881940
- Scalb is 1.968243452
- Efficency is 0.125555121
- Ideal time is 9.870615151

## With 32 threads:
- Speedup is 2.151916569
- Scalb is 2.108384575
- Efficency is 0.067247393
- Ideal time is 4.935307576

Statistics for OMP
## With 1 threads:
- Speedup is 1.011233675
- Scalb is 1.000000000
- Efficency is 1.011233675
- Ideal time is 157.929842419

## With 4 threads:
- Speedup is 1.706440206
- Scalb is 1.687483565
- Efficency is 0.426610051
- Ideal time is 39.482460605

## With 8 threads:
- Speedup is 1.757853184
- Scalb is 1.738325402
- Efficency is 0.219731648
- Ideal time is 19.741230302

## With 16 threads:
- Speedup is 2.007992686
- Scalb is 1.985686134
- Efficency is 0.125499543
- Ideal time is 9.870615151

## With 32 threads:
- Speedup is 2.150544664
- Scalb is 2.126654519
- Efficency is 0.067204521
- Ideal time is 4.935307576


## Sequential of: 3600

- Loading video Time: 103.725786 sec
- Grayscale time : 10.324693008 sec
- GaussianFilter time : 128.711147767 sec
- Comparison time : 6.980483396 sec
- Motion detected in: 102 frames out of 3600
Tot seq time: 249.742899334 sec

# Number of threads 1
-------------------------------------------------------
## Threads
- Loading video Time: 103.713873498 sec

Broadcast message from h.shabir@spm (somewhere) (Sat Jul  9 01:00:00 2022):

system will be busy for 1 hr

- Grayscale time threads: 10.830651129 sec
- Gaussian threads : 136.392083931 sec
- Comparison time : 7.021048235 sec
- Motion detected in: 102 frames out of 3600
- Tot thread time: 257.958415153 sec

## Fast Flow
- Loading video Time: 100.293594316 sec
- Grayscale time : 11.795476573 sec
- GaussianFilter time : 138.386895424 sec
- Comparison time : 7.273539806 sec
- Motion detected in: 102 frames out of 3600
- Tot FastFlow time: 257.752906884 sec

## OpenMP
- Loading video Time: 101.606953462 sec
- Grayscale time : 14.518149818 sec
- GaussianFilter time : 281.759295765 sec
- Comparison time : 16.189198856 sec
- Motion detected in: 102 frames out of 3600
- Tot OpenMp time: 414.074626283 sec
----------------------------------------------------------------

# Number of threads 4
-------------------------------------------------------
## Threads
- Loading video Time: 101.232265361 sec
- Grayscale time threads: 4.617479152 sec
- Gaussian threads : 44.245759359 sec
- Comparison time : 7.010236130 sec
- Motion detected in: 102 frames out of 3600
- Tot thread time: 157.106470162 sec

## Fast Flow
- Loading video Time: 99.595123656 sec
- Grayscale time : 4.672737150 sec
- GaussianFilter time : 88.490426279 sec
- Comparison time : 6.962490010 sec
- Motion detected in: 102 frames out of 3600
- Tot FastFlow time: 199.724171769 sec

## OpenMP
- Loading video Time: 99.608704043 sec
- Grayscale time : 4.600104360 sec
- GaussianFilter time : 54.745177131 sec
- Comparison time : 6.950106047 sec
- Motion detected in: 102 frames out of 3600
- Tot OpenMp time: 165.904804038 sec
----------------------------------------------------------------

# Number of threads 8
-------------------------------------------------------
## Threads
- Loading video Time: 99.967217775 sec
- Grayscale time threads: 2.277637780 sec
- Gaussian threads : 25.083293403 sec
- Comparison time : 7.002393367 sec
- Motion detected in: 102 frames out of 3600
- Tot thread time: 134.331335789 sec

## Fast Flow
- Loading video Time: 100.600424013 sec
- Grayscale time : 4.198232165 sec
- GaussianFilter time : 38.541725541 sec
- Comparison time : 6.910115199 sec
- Motion detected in: 102 frames out of 3600
- Tot FastFlow time: 150.253777382 sec

## OpenMP
- Loading video Time: 100.939277674 sec
- Grayscale time : 2.514567325 sec
- GaussianFilter time : 35.615341100 sec
- Comparison time : 9.251530768 sec
- Motion detected in: 102 frames out of 3600
- Tot OpenMp time: 148.321588938 sec
----------------------------------------------------------------

# Number of threads 16
-------------------------------------------------------
## Threads
- Loading video Time: 101.846172685 sec
- Grayscale time threads: 1.929898186 sec
- Gaussian threads : 27.438522906 sec
- Comparison time : 21.034997836 sec
- Motion detected in: 102 frames out of 3600
- Tot thread time: 152.250340573 sec

## Fast Flow
- Loading video Time: 101.792159677 sec
- Grayscale time : 2.904536044 sec
- GaussianFilter time : 29.587529728 sec
- Comparison time : 21.328550283 sec
- Motion detected in: 102 frames out of 3600
- Tot FastFlow time: 155.624113749 sec

## OpenMP
- Loading video Time: 101.892703348 sec
- Grayscale time : 3.867446697 sec
- GaussianFilter time : 23.685866495 sec
- Comparison time : 6.970889578 sec
- Motion detected in: 102 frames out of 3600
- Tot OpenMp time: 136.417632777 sec
----------------------------------------------------------------

# Number of threads 32
-------------------------------------------------------
## Threads
- Loading video Time: 99.838587228 sec
- Grayscale time threads: 0.950879601 sec
- Gaussian threads : 9.591798738 sec
- Comparison time : 9.393201269 sec
- Motion detected in: 102 frames out of 3600
- Tot thread time: 119.775286703 sec

## Fast Flow
- Loading video Time: 100.078256901 sec
- Grayscale time : 0.763516242 sec
- GaussianFilter time : 8.790539077 sec
- Comparison time : 7.020952294 sec
- Motion detected in: 102 frames out of 3600
- Tot FastFlow time: 116.656612790 sec

## OpenMP
- Loading video Time: 99.582928093 sec
- Grayscale time : 0.747673964 sec
- GaussianFilter time : 9.226721413 sec
- Comparison time : 6.893902364 sec
- Motion detected in: 102 frames out of 3600
- Tot OpenMp time: 116.451956993 sec
----------------------------------------------------------------

Statistics for threads
## With 1 threads:
- Speedup is 0.968151782
- Scalb is 1.000000000
- Efficency is 0.968151782
- Ideal time is 249.742899334

## With 4 threads:
- Speedup is 1.589641083
- Scalb is 1.641933747
- Efficency is 0.397410271
- Ideal time is 62.435724834

## With 8 threads:
- Speedup is 1.859155929
- Scalb is 1.920314524
- Efficency is 0.232394491
- Ideal time is 31.217862417

## With 16 threads:
- Speedup is 1.640343781
- Scalb is 1.694304355
- Efficency is 0.102521486
- Ideal time is 15.608931208

## With 32 threads:
- Speedup is 2.085095400
- Scalb is 2.153686476
- Efficency is 0.065159231
- Ideal time is 7.804465604

Statistics for FF
## With 1 threads:
- Speedup is 0.968923697
- Scalb is 1.000000000
- Efficency is 0.968923697
- Ideal time is 249.742899334

## With 4 threads:
- Speedup is 1.250439029
- Scalb is 1.290544377
- Efficency is 0.312609757
- Ideal time is 62.435724834

## With 8 threads:
- Speedup is 1.662140571
- Scalb is 1.715450429
- Efficency is 0.207767571
- Ideal time is 31.217862417

## With 16 threads:
- Speedup is 1.604782789
- Scalb is 1.656253010
- Efficency is 0.100298924
- Ideal time is 15.608931208

## With 32 threads:
- Speedup is 2.140837912
- Scalb is 2.209501037
- Efficency is 0.066901185
- Ideal time is 7.804465604

Statistics for OMP
## With 1 threads:
- Speedup is 0.603134999
- Scalb is 1.000000000
- Efficency is 0.603134999
- Ideal time is 249.742899334

## With 4 threads:
- Speedup is 1.505338563
- Scalb is 2.495856758
- Efficency is 0.376334641
- Ideal time is 62.435724834

## With 8 threads:
- Speedup is 1.683793311
- Scalb is 2.791735372
- Efficency is 0.210474164
- Ideal time is 31.217862417

## With 16 threads:
- Speedup is 1.830723010
- Scalb is 3.035345342
- Efficency is 0.114420188
- Ideal time is 15.608931208

## With 32 threads:
- Speedup is 2.144600278
- Scalb is 3.555754982
- Efficency is 0.067018759
- Ideal time is 7.804465604