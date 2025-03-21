#include "ShockHashSimdContender.h"

template <int l>
void shockHashSimdTestMulti(size_t N) {
    {ShockHashSimdContender<l>(N, 100).run();}
    {ShockHashSimdContender<l>(N, 500).run();}
    {ShockHashSimdContender<l>(N, 2000).run();}
}

void shockHashSimdContenderRunner(size_t N) {
    shockHashSimdTestMulti<4>(N);
    shockHashSimdTestMulti<6>(N);
    shockHashSimdTestMulti<8>(N);
    shockHashSimdTestMulti<10>(N);
    shockHashSimdTestMulti<12>(N);
    shockHashSimdTestMulti<15>(N);
    shockHashSimdTestMulti<24>(N);
    shockHashSimdTestMulti<28>(N);
    shockHashSimdTestMulti<32>(N);
    shockHashSimdTestMulti<34>(N);
    shockHashSimdTestMulti<36>(N);
    shockHashSimdTestMulti<40>(N);
    shockHashSimdTestMulti<42>(N);
    shockHashSimdTestMulti<44>(N);
    shockHashSimdTestMulti<46>(N);
    shockHashSimdTestMulti<48>(N);
    shockHashSimdTestMulti<50>(N);
    shockHashSimdTestMulti<52>(N);
    shockHashSimdTestMulti<54>(N);
}
