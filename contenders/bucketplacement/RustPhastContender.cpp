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
    for (uint8_t multiplier = 1; multiplier <= 3; ++multiplier) {
        for (size_t bucket_size_100 = 100; bucket_size_100 <= 300; bucket_size_100 += 5)
            RustPhastPlusContender(N, multiplier, 4, bucket_size_100, use_ef).run();
        
        for (size_t bucket_size_100 = 140; bucket_size_100 <= 330; bucket_size_100 += 5)
            RustPhastPlusContender(N, multiplier, 5, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 240; bucket_size_100 <= 350; bucket_size_100 += 5)
            RustPhastPlusContender(N, multiplier, 6, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 300; bucket_size_100 <= 410; bucket_size_100 += 5)
            RustPhastPlusContender(N, multiplier, 7, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 330; bucket_size_100 <= 475; bucket_size_100 += 5)
            RustPhastPlusContender(N, multiplier, 8, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 450; bucket_size_100 <= 530; bucket_size_100 += 5)
            RustPhastPlusContender(N, multiplier, 9, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 510; bucket_size_100 <= 610; bucket_size_100 += 5)
            RustPhastPlusContender(N, multiplier, 10, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 550; bucket_size_100 <= 680; bucket_size_100 += 5)
            RustPhastPlusContender(N, multiplier, 11, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 610; bucket_size_100 <= 740; bucket_size_100 += 5)
            RustPhastPlusContender(N, multiplier, 12, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 690; bucket_size_100 <= 800; bucket_size_100 += 5)
            RustPhastPlusContender(N, multiplier, 13, bucket_size_100, use_ef).run();
    }
}

void rustPHastPlusContenderRunner(size_t N) {
    rustPHastPlusContenderRunnerWithEf(N, true);
    rustPHastPlusContenderRunnerWithEf(N, false);
}

void rustPHastPlusWrappedContenderRunnerWithEf(size_t N, bool use_ef) {
    for (uint8_t multiplier = 1; multiplier <= 3; ++multiplier) {
        for (size_t bucket_size_100 = 100; bucket_size_100 <= 300; bucket_size_100 += 5)
            RustPhastPlusWrappedContender(N, multiplier, 4, bucket_size_100, use_ef).run();
        
        for (size_t bucket_size_100 = 140; bucket_size_100 <= 330; bucket_size_100 += 5)
            RustPhastPlusWrappedContender(N, multiplier, 5, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 240; bucket_size_100 <= 350; bucket_size_100 += 5)
            RustPhastPlusWrappedContender(N, multiplier, 6, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 300; bucket_size_100 <= 410; bucket_size_100 += 5)
            RustPhastPlusWrappedContender(N, multiplier, 7, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 330; bucket_size_100 <= 475; bucket_size_100 += 5)
            RustPhastPlusWrappedContender(N, multiplier, 8, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 450; bucket_size_100 <= 530; bucket_size_100 += 5)
            RustPhastPlusWrappedContender(N, multiplier, 9, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 510; bucket_size_100 <= 610; bucket_size_100 += 5)
            RustPhastPlusWrappedContender(N, multiplier, 10, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 550; bucket_size_100 <= 680; bucket_size_100 += 5)
            RustPhastPlusWrappedContender(N, multiplier, 11, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 610; bucket_size_100 <= 740; bucket_size_100 += 5)
            RustPhastPlusWrappedContender(N, multiplier, 12, bucket_size_100, use_ef).run();

        for (size_t bucket_size_100 = 690; bucket_size_100 <= 800; bucket_size_100 += 5)
            RustPhastPlusWrappedContender(N, multiplier, 13, bucket_size_100, use_ef).run();
    }
}

void rustPHastPlusWrappedContenderRunner(size_t N) {
    rustPHastPlusWrappedContenderRunnerWithEf(N, true);
    rustPHastPlusWrappedContenderRunnerWithEf(N, false);
}