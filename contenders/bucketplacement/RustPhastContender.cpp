#include "RustPhastContender.h"

void rustPHastContenderRunnerWithEf(size_t N, bool use_ef) {
/*  BETTER USE THIS
    for (size_t bucket_size_100 = 100; bucket_size_100 <= 300; bucket_size_100 += 5)
        RustPhastContender(N, 4, bucket_size_100).run();
    
    for (size_t bucket_size_100 = 180; bucket_size_100 <= 330; bucket_size_100 += 10)
        RustPhastContender(N, 5, bucket_size_100).run();

    for (size_t bucket_size_100 = 290; bucket_size_100 <= 360; bucket_size_100 += 10)
        RustPhastContender(N, 6, bucket_size_100).run();

    for (size_t bucket_size_100 = 340; bucket_size_100 <= 410; bucket_size_100 += 10)
        RustPhastContender(N, 7, bucket_size_100).run();
    for (size_t bucket_size_100 = 355; bucket_size_100 <= 415; bucket_size_100 += 10)
        RustPhastContender(N, 7, bucket_size_100).run();

    for (size_t bucket_size_100 = 390; bucket_size_100 <= 490; bucket_size_100 += 5)
        RustPhastContender(N, 8, bucket_size_100).run();

    for (size_t bucket_size_100 = 470; bucket_size_100 <= 550; bucket_size_100 += 10)
        RustPhastContender(N, 9, bucket_size_100).run();

    for (size_t bucket_size_100 = 530; bucket_size_100 <= 620; bucket_size_100 += 10)
        RustPhastContender(N, 10, bucket_size_100).run();

    for (size_t bucket_size_100 = 580; bucket_size_100 <= 690; bucket_size_100 += 10)
        RustPhastContender(N, 11, bucket_size_100).run();
    RustPhastContender(N, 11, 675).run();
    RustPhastContender(N, 11, 685).run();

    for (size_t bucket_size_100 = 650; bucket_size_100 <= 750; bucket_size_100 += 10)
        RustPhastContender(N, 12, bucket_size_100).run();
    RustPhastContender(N, 12, 735).run();
    RustPhastContender(N, 12, 745).run();

    for (size_t bucket_size_100 = 710; bucket_size_100 <= 820; bucket_size_100 += 10)
        RustPhastContender(N, 13, bucket_size_100).run();
*/

    for (size_t bucket_size_100 = 100; bucket_size_100 <= 300; bucket_size_100 += 5)
        RustPhastContender(N, 4, bucket_size_100, use_ef).run();
    
    for (size_t bucket_size_100 = 160; bucket_size_100 <= 330; bucket_size_100 += 10)
        RustPhastContender(N, 5, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 260; bucket_size_100 <= 350; bucket_size_100 += 10)
        RustPhastContender(N, 6, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 320; bucket_size_100 <= 410; bucket_size_100 += 10)
        RustPhastContender(N, 7, bucket_size_100, use_ef).run();
    RustPhastContender(N, 7, 395, use_ef).run();
    RustPhastContender(N, 7, 405, use_ef).run();

    for (size_t bucket_size_100 = 350; bucket_size_100 <= 380; bucket_size_100 += 10)
        RustPhastContender(N, 8, bucket_size_100, use_ef).run();
    for (size_t bucket_size_100 = 390; bucket_size_100 <= 475; bucket_size_100 += 5)
        RustPhastContender(N, 8, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 470; bucket_size_100 <= 530; bucket_size_100 += 20)
        RustPhastContender(N, 9, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 530; bucket_size_100 <= 610; bucket_size_100 += 10)
        RustPhastContender(N, 10, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 570; bucket_size_100 <= 680; bucket_size_100 += 10)
        RustPhastContender(N, 11, bucket_size_100, use_ef).run();
    RustPhastContender(N, 11, 675, use_ef).run();

    for (size_t bucket_size_100 = 650; bucket_size_100 <= 740; bucket_size_100 += 10)
        RustPhastContender(N, 12, bucket_size_100, use_ef).run();
    RustPhastContender(N, 12, 735, use_ef).run();

    for (size_t bucket_size_100 = 710; bucket_size_100 <= 800; bucket_size_100 += 10)
        RustPhastContender(N, 13, bucket_size_100, use_ef).run();
}

void rustPHastContenderRunner(size_t N) {
    rustPHastContenderRunnerWithEf(N, true);
    rustPHastContenderRunnerWithEf(N, false);
}


void rustPHastPlusContenderRunnerWithEf(size_t N, bool use_ef) {
    for (size_t bucket_size_100 = 220; bucket_size_100 <= 410; bucket_size_100 += 5)
        RustPhastPlusContender(N, 1, 6, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 290; bucket_size_100 <= 480; bucket_size_100 += 5)
        RustPhastPlusContender(N, 1, 7, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 330; bucket_size_100 <= 540; bucket_size_100 += 5)
        RustPhastPlusContender(N, 1, 8, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 400; bucket_size_100 <= 570; bucket_size_100 += 5)
        RustPhastPlusContender(N, 1, 9, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 350; bucket_size_100 <= 620; bucket_size_100 += 5)
        RustPhastPlusContender(N, 1, 10, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 380; bucket_size_100 <= 680; bucket_size_100 += 5)
        RustPhastPlusContender(N, 1, 11, bucket_size_100, use_ef).run();

    for (size_t bucket_size_100 = 400; bucket_size_100 <= 715; bucket_size_100 += 5)
        RustPhastPlusContender(N, 1, 12, bucket_size_100, use_ef).run();
}

void rustPHastPlusContenderRunner(size_t N) {
    rustPHastPlusContenderRunnerWithEf(N, true);
    rustPHastPlusContenderRunnerWithEf(N, false);
}

void rustPHastPlusWrappedContenderRunnerWithEf(size_t N, bool use_ef) {
    // ---------- multiplier 1 ----------
    for (size_t bucket_size_100 = 370; bucket_size_100 <= 540; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 1, 8, bucket_size_100, 512, use_ef).run();
    for (size_t bucket_size_100 = 360; bucket_size_100 <= 540; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 1, 8, bucket_size_100, 1024, use_ef).run();

    for (size_t bucket_size_100 = 440; bucket_size_100 <= 565; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 1, 9, bucket_size_100, 0, use_ef).run();

    for (size_t bucket_size_100 = 430; bucket_size_100 <= 660; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 1, 10, bucket_size_100, 1024, use_ef).run();
    for (size_t bucket_size_100 = 420; bucket_size_100 <= 645; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 1, 10, bucket_size_100, 2048, use_ef).run();
    
    for (size_t bucket_size_100 = 420; bucket_size_100 <= 695; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 1, 11, bucket_size_100, 0, use_ef).run();

    for (size_t bucket_size_100 = 460; bucket_size_100 <= 750; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 1, 12, bucket_size_100, 0, use_ef).run();


    // ---------- multiplier 2 ----------
    for (size_t bucket_size_100 = 350; bucket_size_100 <= 515; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 2, 8, bucket_size_100, 0, use_ef).run();

    for (size_t bucket_size_100 = 390; bucket_size_100 <= 580; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 2, 9, bucket_size_100, 1024, use_ef).run();
    for (size_t bucket_size_100 = 390; bucket_size_100 <= 580; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 2, 9, bucket_size_100, 2048, use_ef).run();

    for (size_t bucket_size_100 = 400; bucket_size_100 <= 640; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 2, 10, bucket_size_100, 0, use_ef).run();

    for (size_t bucket_size_100 = 445; bucket_size_100 <= 690; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 2, 11, bucket_size_100, 0, use_ef).run();


    // ---------- multiplier 3 ----------
    for (size_t bucket_size_100 = 340; bucket_size_100 <= 510; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 3, 8, bucket_size_100, 0, use_ef).run();
    
    for (size_t bucket_size_100 = 390; bucket_size_100 <= 570; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 3, 9, bucket_size_100, 0, use_ef).run();

    for (size_t bucket_size_100 = 360; bucket_size_100 <= 620; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 3, 10, bucket_size_100, 2048, use_ef).run();
    for (size_t bucket_size_100 = 360; bucket_size_100 <= 640; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 3, 10, bucket_size_100, 4096, use_ef).run();

    for (size_t bucket_size_100 = 360; bucket_size_100 <= 685; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 3, 11, bucket_size_100, 0, use_ef).run();

    for (size_t bucket_size_100 = 450; bucket_size_100 <= 750; bucket_size_100 += 5)
        RustPhastPlusWrappedContender(N, 3, 12, bucket_size_100, 0, use_ef).run();
}

void rustPHastPlusWrappedContenderRunner(size_t N) {
    rustPHastPlusWrappedContenderRunnerWithEf(N, true);
    rustPHastPlusWrappedContenderRunnerWithEf(N, false);
}