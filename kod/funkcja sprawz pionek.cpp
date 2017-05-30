void Gra::sprawdzMBpionek(int kol) {

    wyzerujMRpionek();

    for (i=2; i<10; i++)
    for (j=2; j<10; j++){
        switch(planszagry[i][j]){
            case 1: {
                if (kol==1) {
                    if (planszagry[i-2][j-2]==0 && (planszagry[i-1][j-1]==2 || planszagry[i-1][j-1]==12 || planszagry[i-1][j-1]==-2 || planszagry[i-1][j-1]==-12) && zbite_pionki[i-1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i-2][j+2]==0 && (planszagry[i-1][j+1]==2 || planszagry[i-1][j+1]==12 || planszagry[i-1][j+1]==-2 || planszagry[i-1][j+1]==-12) && zbite_pionki[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j-2]==0 && (planszagry[i+1][j-1]==2 || planszagry[i+1][j-1]==12 || planszagry[i+1][j-1]==-2 || planszagry[i+1][j-1]==-12) && zbite_pionki[i+1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j+2]==0 && (planszagry[i+1][j+1]==2 || planszagry[i+1][j+1]==12 || planszagry[i+1][j+1]==-2 || planszagry[i+1][j+1]==-12) && zbite_pionki[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                }
            } break;
            case -1: {
                if (kol==1) {
                    if (planszagry[i-2][j-2]==0 && (planszagry[i-1][j-1]==2 || planszagry[i-1][j-1]==12 || planszagry[i-1][j-1]==-2 || planszagry[i-1][j-1]==-12) && zbite_pionki[i-1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i-2][j+2]==0 && (planszagry[i-1][j+1]==2 || planszagry[i-1][j+1]==12 || planszagry[i-1][j+1]==-2 || planszagry[i-1][j+1]==-12) && zbite_pionki[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j-2]==0 && (planszagry[i+1][j-1]==2 || planszagry[i+1][j-1]==12 || planszagry[i+1][j-1]==-2 || planszagry[i+1][j-1]==-12) && zbite_pionki[i+1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j+2]==0 && (planszagry[i+1][j+1]==2 || planszagry[i+1][j+1]==12 || planszagry[i+1][j+1]==-2 || planszagry[i+1][j+1]==-12) && zbite_pionki[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                }
            } break;
            case 2: {
                if (kol==2) {
                    if (planszagry[i-2][j-2]==0 && (planszagry[i-1][j-1]==1 || planszagry[i-1][j-1]==11 || planszagry[i-1][j-1]==-1 || planszagry[i-1][j-1]==-11) && zbite_pionki[i-1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i-2][j+2]==0 && (planszagry[i-1][j+1]==1 || planszagry[i-1][j+1]==11 || planszagry[i-1][j+1]==-1 || planszagry[i-1][j+1]==-11) && zbite_pionki[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j-2]==0 && (planszagry[i+1][j-1]==1 || planszagry[i+1][j-1]==11 || planszagry[i+1][j-1]==-1 || planszagry[i+1][j-1]==-11) && zbite_pionki[i+1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j+2]==0 && (planszagry[i+1][j+1]==1 || planszagry[i+1][j+1]==11 || planszagry[i+1][j+1]==-1 || planszagry[i+1][j+1]==-11) && zbite_pionki[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                }
            } break;
            case -2: {
                if (kol==2) {
                    if (planszagry[i-2][j-2]==0 && (planszagry[i-1][j-1]==1 || planszagry[i-1][j-1]==11 || planszagry[i-1][j-1]==-1 || planszagry[i-1][j-1]==-11) && zbite_pionki[i-1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i-2][j+2]==0 && (planszagry[i-1][j+1]==1 || planszagry[i-1][j+1]==11 || planszagry[i-1][j+1]==-1 || planszagry[i-1][j+1]==-11) && zbite_pionki[i-1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j-2]==0 && (planszagry[i+1][j-1]==1 || planszagry[i+1][j-1]==11 || planszagry[i+1][j-1]==-1 || planszagry[i+1][j-1]==-11) && zbite_pionki[i+1][j-1]==0)
                        MRpionek[i-2][j-2] = 1;
                    if (planszagry[i+2][j+2]==0 && (planszagry[i+1][j+1]==1 || planszagry[i+1][j+1]==11 || planszagry[i+1][j+1]==-1 || planszagry[i+1][j+1]==-11) && zbite_pionki[i+1][j+1]==0)
                        MRpionek[i-2][j-2] = 1;
                }
            } break;
            case 11: {
                if (kol==1) {
                    for (tmp=0; tmp<7; tmp++) {
                        if (zbite_pionki[i+1+tmp][j-1-tmp]==1 || planszagry[i+1+tmp][j-1-tmp]==1 || planszagry[i+1+tmp][j-1-tmp]==11 || planszagry[i+1+tmp][j-1-tmp]==-1 || planszagry[i+1+tmp][j-1-tmp]==-11)
                            break;
                        if ((planszagry[i+1+tmp][j-1-tmp]==2 || planszagry[i+1+tmp][j-1-tmp]==12 || planszagry[i+1+tmp][j-1-tmp]==-2 || planszagry[i+1+tmp][j-1-tmp]==-12) && zbite_pionki[i+1+tmp][j-1-tmp]==0) {
                         if (planszagry[i+2+tmp][j-2-tmp]==0)
                            MRpionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                    for (tmp=0; tmp<7; tmp++) {
                        if (zbite_pionki[i+1+tmp][j+1+tmp]==1 || planszagry[i+1+tmp][j+1+tmp]==1 || planszagry[i+1+tmp][j+1+tmp]==11 || planszagry[i+1+tmp][j-1-tmp]==-1 || planszagry[i+1+tmp][j-1-tmp]==-11)
                            break;
                        if ((planszagry[i+1+tmp][j+1+tmp]==2 || planszagry[i+1+tmp][j+1+tmp]==12 || planszagry[i+1+tmp][j+1+tmp]==-2 || planszagry[i+1+tmp][j+1+tmp]==-12) && zbite_pionki[i+1+tmp][j+1+tmp]==0) {
                         if (planszagry[i+2+tmp][j+2+tmp]==0)
                            MRpionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                    for (tmp=0; tmp<7; tmp++) {
                        if (zbite_pionki[i-1-tmp][j-1-tmp]==1 || planszagry[i-1-tmp][j-1-tmp]==1 || planszagry[i-1-tmp][j-1-tmp]==11 || planszagry[i+1+tmp][j-1-tmp]==-1 || planszagry[i+1+tmp][j-1-tmp]==-11)
                            break;
                        if ((planszagry[i-1-tmp][j-1-tmp]==2 || planszagry[i-1-tmp][j-1-tmp]==12 || planszagry[i-1-tmp][j-1-tmp]==-2 || planszagry[i-1-tmp][j-1-tmp]==-12) && zbite_pionki[i-1-tmp][j-1-tmp]==0) {
                         if (planszagry[i-2-tmp][j-2-tmp]==0)
                            MRpionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                    for (tmp=0; tmp<7; tmp++) {
                        if (zbite_pionki[i-1-tmp][j+1+tmp]==1 || planszagry[i-1-tmp][j+1+tmp]==1 || planszagry[i-1-tmp][j+1+tmp]==11 || planszagry[i+1+tmp][j-1-tmp]==-1 || planszagry[i+1+tmp][j-1-tmp]==-11)
                            break;
                        if ((planszagry[i-1-tmp][j+1+tmp]==2 || planszagry[i-1-tmp][j+1+tmp]==12 || planszagry[i-1-tmp][j+1+tmp]==-2 || planszagry[i-1-tmp][j+1+tmp]==-12) && zbite_pionki[i-1-tmp][j+1+tmp]==0) {
                         if (planszagry[i-2-tmp][j+2+tmp]==0)
                            MRpionek[i-2][j-2] = 1;
                         break;
                        }
                    }
                }
            } break;
            case -11: {
                    if (kol==1) {
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i+1+tmp][j-1-tmp]==1 || planszagry[i+1+tmp][j-1-tmp]==1 || planszagry[i+1+tmp][j-1-tmp]==11)
                                break;
                            if ((planszagry[i+1+tmp][j-1-tmp]==2 || planszagry[i+1+tmp][j-1-tmp]==12 || planszagry[i+1+tmp][j-1-tmp]==-2 || planszagry[i+1+tmp][j-1-tmp]==-12) && zbite_pionki[i+1+tmp][j-1-tmp]==0) {
                             if (planszagry[i+2+tmp][j-2-tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i+1+tmp][j+1+tmp]==1 || planszagry[i+1+tmp][j+1+tmp]==1 || planszagry[i+1+tmp][j+1+tmp]==11)
                                break;
                            if ((planszagry[i+1+tmp][j+1+tmp]==2 || planszagry[i+1+tmp][j+1+tmp]==12 || planszagry[i+1+tmp][j+1+tmp]==-2 || planszagry[i+1+tmp][j+1+tmp]==-12) && zbite_pionki[i+1+tmp][j+1+tmp]==0) {
                             if (planszagry[i+2+tmp][j+2+tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i-1-tmp][j-1-tmp]==1 || planszagry[i-1-tmp][j-1-tmp]==1 || planszagry[i-1-tmp][j-1-tmp]==11)
                                break;
                            if ((planszagry[i-1-tmp][j-1-tmp]==2 || planszagry[i-1-tmp][j-1-tmp]==12 || planszagry[i-1-tmp][j-1-tmp]==-2 || planszagry[i-1-tmp][j-1-tmp]==-12) && zbite_pionki[i-1-tmp][j-1-tmp]==0) {
                             if (planszagry[i-2-tmp][j-2-tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i-1-tmp][j+1+tmp]==1 || planszagry[i-1-tmp][j+1+tmp]==1 || planszagry[i-1-tmp][j+1+tmp]==11)
                                break;
                            if ((planszagry[i-1-tmp][j+1+tmp]==2 || planszagry[i-1-tmp][j+1+tmp]==12 || planszagry[i-1-tmp][j+1+tmp]==-2 || planszagry[i-1-tmp][j+1+tmp]==-12) && zbite_pionki[i-1-tmp][j+1+tmp]==0) {
                             if (planszagry[i-2-tmp][j+2+tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                    }
            } break;
            case 12: {
                    if (kol==2) {
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i+1+tmp][j-1-tmp]==1 || planszagry[i+1+tmp][j-1-tmp]==2 || planszagry[i+1+tmp][j-1-tmp]==12 || planszagry[i+1+tmp][j-1-tmp]==-2 || planszagry[i+1+tmp][j-1-tmp]==-12)
                                break;
                            if ((planszagry[i+1+tmp][j-1-tmp]==1 || planszagry[i+1+tmp][j-1-tmp]==11 || planszagry[i+1+tmp][j-1-tmp]==-1 || planszagry[i+1+tmp][j-1-tmp]==-11) && zbite_pionki[i+1+tmp][j-1-tmp]==0) {
                             if (planszagry[i+2+tmp][j-2-tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i+1+tmp][j+1+tmp]==1 || planszagry[i+1+tmp][j+1+tmp]==2 || planszagry[i+1+tmp][j+1+tmp]==12 || planszagry[i+1+tmp][j-1-tmp]==-2 || planszagry[i+1+tmp][j-1-tmp]==-12)
                                break;
                            if ((planszagry[i+1+tmp][j+1+tmp]==1 || planszagry[i+1+tmp][j+1+tmp]==11 || planszagry[i+1+tmp][j+1+tmp]==-1 || planszagry[i+1+tmp][j+1+tmp]==-11) && zbite_pionki[i+1+tmp][j+1+tmp]==0) {
                             if (planszagry[i+2+tmp][j+2+tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i-1-tmp][j-1-tmp]==1 || planszagry[i-1-tmp][j-1-tmp]==2 || planszagry[i-1-tmp][j-1-tmp]==12 || planszagry[i+1+tmp][j-1-tmp]==-2 || planszagry[i+1+tmp][j-1-tmp]==-12)
                                break;
                            if ((planszagry[i-1-tmp][j-1-tmp]==1 || planszagry[i-1-tmp][j-1-tmp]==11 || planszagry[i-1-tmp][j-1-tmp]==-1 || planszagry[i-1-tmp][j-1-tmp]==-11) && zbite_pionki[i-1-tmp][j-1-tmp]==0) {
                             if (planszagry[i-2-tmp][j-2-tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i-1-tmp][j+1+tmp]==1 || planszagry[i-1-tmp][j+1+tmp]==2 || planszagry[i-1-tmp][j+1+tmp]==12 || planszagry[i+1+tmp][j-1-tmp]==-2 || planszagry[i+1+tmp][j-1-tmp]==-12)
                                break;
                            if ((planszagry[i-1-tmp][j+1+tmp]==1 || planszagry[i-1-tmp][j+1+tmp]==11 || planszagry[i-1-tmp][j+1+tmp]==-1 || planszagry[i-1-tmp][j+1+tmp]==-11) && zbite_pionki[i-1-tmp][j+1+tmp]==0) {
                             if (planszagry[i-2-tmp][j+2+tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                    }
            } break;
            case -12: {
                    if (kol==2) {
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i+1+tmp][j-1-tmp]==1 || planszagry[i+1+tmp][j-1-tmp]==2 || planszagry[i+1+tmp][j-1-tmp]==12)
                                break;
                            if ((planszagry[i+1+tmp][j-1-tmp]==1 || planszagry[i+1+tmp][j-1-tmp]==11 || planszagry[i+1+tmp][j-1-tmp]==-1 || planszagry[i+1+tmp][j-1-tmp]==-11) && zbite_pionki[i+1+tmp][j-1-tmp]==0) {
                             if (planszagry[i+2+tmp][j-2-tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i+1+tmp][j+1+tmp]==1 || planszagry[i+1+tmp][j+1+tmp]==2 || planszagry[i+1+tmp][j+1+tmp]==12)
                                break;
                            if ((planszagry[i+1+tmp][j+1+tmp]==1 || planszagry[i+1+tmp][j+1+tmp]==11 || planszagry[i+1+tmp][j+1+tmp]==-1 || planszagry[i+1+tmp][j+1+tmp]==-11) && zbite_pionki[i+1+tmp][j+1+tmp]==0) {
                             if (planszagry[i+2+tmp][j+2+tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i-1-tmp][j-1-tmp]==1 || planszagry[i-1-tmp][j-1-tmp]==2 || planszagry[i-1-tmp][j-1-tmp]==12)
                                break;
                            if ((planszagry[i-1-tmp][j-1-tmp]==1 || planszagry[i-1-tmp][j-1-tmp]==11 || planszagry[i-1-tmp][j-1-tmp]==-1 || planszagry[i-1-tmp][j-1-tmp]==-11) && zbite_pionki[i-1-tmp][j-1-tmp]==0) {
                             if (planszagry[i-2-tmp][j-2-tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                        for (tmp=0; tmp<7; tmp++) {
                            if (zbite_pionki[i-1-tmp][j+1+tmp]==1 || planszagry[i-1-tmp][j+1+tmp]==2 || planszagry[i-1-tmp][j+1+tmp]==12)
                                break;
                            if ((planszagry[i-1-tmp][j+1+tmp]==1 || planszagry[i-1-tmp][j+1+tmp]==11 || planszagry[i-1-tmp][j+1+tmp]==-1 || planszagry[i-1-tmp][j+1+tmp]==-11) && zbite_pionki[i-1-tmp][j+1+tmp]==0) {
                             if (planszagry[i-2-tmp][j+2+tmp]==0)
                                MRpionek[i-2][j-2] = 1;
                             break;
                            }
                        }
                    }
            } break;
            default: {}
        }
    }
} 
