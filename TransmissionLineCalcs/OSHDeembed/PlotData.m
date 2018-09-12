

tline = sparameters('THRU.S2P');
reflect = sparameters('OPENSHORTMAG.S2P');
phaseref = sparameters('OPENSHORTPHASE.S2P');

figure();
rfplot(tline);


figure();
rfplot(reflect);

figure();
rfplot(phaseref);