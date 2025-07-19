#include <tlx/cmdline_parser.hpp>

#include "bucketplacement/PhobicContender.h"
#include "bucketplacement/PartitionedPTHashContender.h"
#include "fingerprinting/FiPSContender.h"
#include "fingerprinting/RustFmphContender.h"
#include "bucketplacement/PTHashContender.h"
#include "fingerprinting/RustFmphGoContender.h"
#include "recsplit/SIMDRecSplitContender.h"
#include "retrievalbased/SicHashContender.h"
#include "shockhash/BipartiteShockHashFlatContender.h"
#include "bucketplacement/ChdContender.h"
#include "bucketplacement/RustPhastContender.h"
#include "bucketplacement/RustPtrHashContender.h"
#include "consensus/ConsensusContender.h"

/**
* Comparison table used in "PHast".
*/
int main(int argc, char** argv) {
    size_t N = 5e6;
    tlx::CmdlineParser cmd;
    cmd.add_bytes('n', "numKeys", N, "Number of objects");
    cmd.add_bytes('q', "numQueries", Contender::numQueries, "Number of queries over all keys to perform");
    cmd.add_bytes('t', "numThreads", Contender::numThreads, "Number of threads to use for construction");
    cmd.add_flag('T', "skipTests", Contender::skipTests, "Skip testing PHF for validity");
    cmd.add_bytes('s', "seed", Contender::seed, "Seed for pseudo-number generator");

    bool all = false;
    bool most = false;
    bool rest = false;
    bool simdrecsplit = false;
    bool sichash = false;
    bool sichash1 = false;
    bool sichash2 = false;
    bool pthash = false;
    bool partitionedPthash = false;
    bool rustFmphContender = false;
    bool rustFmphGoContender = false;
    bool rustPhastContender = false;
    bool rustPhastContenderEF = false;
    bool rustPhastContenderC = false;
    bool rustPhastPlusContender = false;
    bool rustPhastPlusContenderEF = false;
    bool rustPhastPlusContenderC = false;
    bool rustPtrHashContender = false;
    bool rustPtrHashGxContender = false;
    bool densePartitionedPtHash = false;
    bool bipartiteShockHashFlat = false;

    cmd.add_flag("all", all, "Execute all benchmarks");
    cmd.add_flag("most", most, "Execute most benchmarks");
    cmd.add_flag("rest", rest, "Execute most but not PHast benchmarks");
    cmd.add_flag("simdrecsplit", simdrecsplit, "Execute SIMDRecSplit benchmark");
    cmd.add_flag("sichash", sichash, "Execute sichash benchmark");
    cmd.add_flag("sichash1", sichash1, "Execute sichash 1 benchmark");
    cmd.add_flag("sichash2", sichash2, "Execute sichash 2 benchmark");
    //cmd.add_flag("bipartiteShockHash", bipartiteShockHash, "Execute bipartite shockhash benchmark");
    cmd.add_flag("bipartiteShockHashFlat", bipartiteShockHashFlat, "Execute bipartite shockhash flat benchmark");
    cmd.add_flag("pthash", pthash, "Execute pthash benchmark");
    cmd.add_flag("partitionedPthash", partitionedPthash, "Execute partitioned pthash benchmark");
    cmd.add_flag("densePartitionedPtHash", densePartitionedPtHash, "Execute dense partitioend PTHash benchmark");
    cmd.add_flag("rustFmph", rustFmphContender, "Execute rust fmph benchmark");
    cmd.add_flag("rustFmphGo", rustFmphGoContender, "Execute rust fmph-go benchmark");
    cmd.add_flag("rustPHast", rustPhastContender, "Execute all rust PHast benchmark");
    cmd.add_flag("rustPHastEF", rustPhastContenderEF, "Execute rust PHast with EF encoding benchmark");
    cmd.add_flag("rustPHastC", rustPhastContenderC, "Execute rust PHast with C encoding benchmark");
    cmd.add_flag("rustPHastPlus", rustPhastPlusContender, "Execute all rust PHast+ benchmark");
    cmd.add_flag("rustPHastPlusEF", rustPhastPlusContenderEF, "Execute rust PHast+ with EF encoding benchmark");
    cmd.add_flag("rustPHastPlusC", rustPhastPlusContenderC, "Execute rust PHast+ with C encoding benchmark");
    cmd.add_flag("rustPtrHash", rustPtrHashContender, "Execute rust ptrhash benchmark");
    cmd.add_flag("rustPtrHashGx", rustPtrHashGxContender, "Execute rust ptrhash benchmark");


    if (!cmd.process(argc, argv)) {
        return 1;
    }

    //{RustPhastContender(N, 8, 425).run();}
    //{RustPtrHashContender(N, RustPtrHashContender::VARIANT_LINEAR_VEC, 3.0).run();} // Fast
    //{RustPtrHashGxContender(N, RustPtrHashContender::VARIANT_CUBIC_EF, 3.5).run();}

    if (all || most || rustPhastContender || rustPhastContenderEF) {
        {RustPhastContender(N, 4, 260, true).run();} //2
        //{RustPhastContender(N, 4, 290, true).run();} //3
    
        {RustPhastContender(N, 5, 260, true).run();} //2
        {RustPhastContender(N, 5, 280, true).run();} //1
        //{RustPhastContender(N, 5, 300, true).run();} //3 
        //{RustPhastContender(N, 5, 320, true).run();} //3
    
        //{RustPhastContender(N, 6, 280, true).run();} //3
        //{RustPhastContender(N, 6, 300, true).run();} //3
        {RustPhastContender(N, 6, 320, true).run();} //2
        {RustPhastContender(N, 6, 340, true).run();} //3
    
        //{RustPhastContender(N, 7, 350, true).run();} //3
        {RustPhastContender(N, 7, 370, true).run();} //1
        {RustPhastContender(N, 7, 390, true).run();} //2
    
        {RustPhastContender(N, 8, 410, true).run();} //1
        {RustPhastContender(N, 8, 420, true).run();} //1
        {RustPhastContender(N, 8, 430, true).run();} //1
        {RustPhastContender(N, 8, 450, true).run();} //1
        //{RustPhastContender(N, 8, 460, true).run();} //3
    
        {RustPhastContender(N, 9, 510, true).run();} //2
        {RustPhastContender(N, 9, 530, true).run();} //2
    
        //{RustPhastContender(N, 10, 560, true).run();} //3
        //{RustPhastContender(N, 10, 580, true).run();} //3
        {RustPhastContender(N, 10, 600, true).run();} //1
    
        {RustPhastContender(N, 11, 630, true).run();} //2
        {RustPhastContender(N, 11, 650, true).run();} //2
        //{RustPhastContender(N, 11, 670, true).run();} //3
    
        //{RustPhastContender(N, 12, 680, true).run();}   // worse than (11, 630) //3
        {RustPhastContender(N, 12, 700, true).run();} //2
        {RustPhastContender(N, 12, 720, true).run();} //2
    }

    if (all || most || rustPhastContender || rustPhastContenderC) {
        {RustPhastContender(N, 8, 410, false).run();}  //2
        {RustPhastContender(N, 8, 420, false).run();}  //1
        //{RustPhastContender(N, 8, 430, false).run();} //3
        //{RustPhastContender(N, 8, 450, false).run();} //3
        //{RustPhastContender(N, 8, 460, false).run();} //3
    }

    if (all || most || rustPhastPlusContender || rustPhastPlusContenderEF) {
        {RustPhastPlusContender(N, 8, 410, true).run();} //1
        {RustPhastPlusContender(N, 8, 415, true).run();} //1
        {RustPhastPlusContender(N, 8, 420, true).run();} //1
        {RustPhastPlusContender(N, 8, 430, true).run();} //1
        {RustPhastPlusContender(N, 8, 450, true).run();} //1
        {RustPhastPlusContender(N, 8, 500, true).run();} //1

        {RustPhastPlusContender(N, 9, 480, true).run();} //1
        {RustPhastPlusContender(N, 9, 515, true).run();} //1
        {RustPhastPlusContender(N, 9, 550, true).run();} //1

        {RustPhastPlusContender(N, 10, 515, true).run();} //1
        {RustPhastPlusContender(N, 10, 595, true).run();} //1

        {RustPhastPlusContender(N, 11, 570, true).run();}
        {RustPhastPlusContender(N, 11, 575, true).run();}
        {RustPhastPlusContender(N, 11, 650, true).run();}

        {RustPhastPlusContender(N, 12, 620, true).run();}
        {RustPhastPlusContender(N, 12, 660, true).run();}


        {RustPhastPlusWrappedContender(N, 1, 8, 415, 512, true).run();} //1
        {RustPhastPlusWrappedContender(N, 1, 8, 500, 512, true).run();} //1
        {RustPhastPlusWrappedContender(N, 1, 8, 430, 1024, true).run();} //1
        {RustPhastPlusWrappedContender(N, 1, 8, 470, 1024, true).run();} //1

        {RustPhastPlusWrappedContender(N, 1, 9, 485, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 1, 9, 550, 0, true).run();} //1

        {RustPhastPlusWrappedContender(N, 1, 10, 580, 1024, true).run();} //1
        {RustPhastPlusWrappedContender(N, 1, 10, 620, 1024, true).run();} //1

        {RustPhastPlusWrappedContender(N, 1, 10, 555, 2048, true).run();} //1
        {RustPhastPlusWrappedContender(N, 1, 10, 620, 2048, true).run();} //1

        {RustPhastPlusWrappedContender(N, 1, 11, 610, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 1, 11, 660, 0, true).run();} //1

        {RustPhastPlusWrappedContender(N, 1, 12, 670, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 1, 12, 710, 0, true).run();} //1


        {RustPhastPlusWrappedContender(N, 2, 8, 430, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 2, 8, 435, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 2, 8, 450, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 2, 8, 470, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 2, 8, 490, 0, true).run();} //1

        {RustPhastPlusWrappedContender(N, 2, 9, 485, 1024, true).run();} //1   +- 5
        {RustPhastPlusWrappedContender(N, 2, 9, 545, 1024, true).run();}
        {RustPhastPlusWrappedContender(N, 2, 9, 550, 1024, true).run();}

        {RustPhastPlusWrappedContender(N, 2, 9, 495, 2048, true).run();}
        {RustPhastPlusWrappedContender(N, 2, 9, 500, 2048, true).run();}
        {RustPhastPlusWrappedContender(N, 2, 9, 540, 2048, true).run();}

        {RustPhastPlusWrappedContender(N, 2, 10, 555, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 2, 10, 590, 0, true).run();}

        {RustPhastPlusWrappedContender(N, 2, 11, 610, 0, true).run();}
        {RustPhastPlusWrappedContender(N, 2, 11, 660, 0, true).run();}


        {RustPhastPlusWrappedContender(N, 3, 8, 435, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 3, 8, 480, 0, true).run();} //1

        {RustPhastPlusWrappedContender(N, 3, 9, 485, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 3, 9, 520, 0, true).run();} //1
        {RustPhastPlusWrappedContender(N, 3, 9, 525, 0, true).run();} //1

        {RustPhastPlusWrappedContender(N, 3, 10, 555, 2048, true).run();} //1
        {RustPhastPlusWrappedContender(N, 3, 10, 580, 2048, true).run();} //1
        {RustPhastPlusWrappedContender(N, 3, 10, 600, 2048, true).run();} //1

        {RustPhastPlusWrappedContender(N, 3, 10, 555, 4096, true).run();} //1
        {RustPhastPlusWrappedContender(N, 3, 10, 575, 4096, true).run();}
        {RustPhastPlusWrappedContender(N, 3, 10, 580, 4096, true).run();} //1   or 575

        {RustPhastPlusWrappedContender(N, 3, 11, 600, 0, true).run();}
        {RustPhastPlusWrappedContender(N, 3, 11, 610, 0, true).run();}
        {RustPhastPlusWrappedContender(N, 3, 11, 640, 0, true).run();}

        {RustPhastPlusWrappedContender(N, 3, 12, 680, 0, true).run();}
        {RustPhastPlusWrappedContender(N, 3, 12, 710, 0, true).run();}
    }

    /*if (all || most || rustPtrHashContender) {
        {RustPtrHashContender(N, RustPtrHashContender::VARIANT_LINEAR_VEC, 3.0).run();} // Fast
        //{RustPtrHashContender(N, RustPtrHashContender::VARIANT_LINEAR_EF, 3.0).run();}  //2
        {RustPtrHashContender(N, RustPtrHashContender::VARIANT_CUBIC_EF, 3.5).run();}   // Default
        {RustPtrHashContender(N, RustPtrHashContender::VARIANT_CUBIC_EF, 4.0).run();}   // Compact
    }*/

    if (all || most || /*rest ||*/ rustPtrHashGxContender) {
        {RustPtrHashGxContender(N, RustPtrHashContender::VARIANT_LINEAR_VEC, 3.0).run();} // Fast
        {RustPtrHashGxContender(N, RustPtrHashContender::VARIANT_LINEAR_EF, 3.0).run();}    //2
        {RustPtrHashGxContender(N, RustPtrHashContender::VARIANT_CUBIC_EF, 3.5).run();}   // Default
        {RustPtrHashGxContender(N, RustPtrHashContender::VARIANT_CUBIC_EF, 4.0).run();}   // Compact
    }

    if (all || most || rest || pthash) {
        {PTHashContender<true, pthash::compact_compact>(N, 0.99, 4.0).run();}
        {PTHashContender<true, pthash::elias_fano>(N, 0.99, 5.0).run();}
    }
    
    if (all || most || rest || partitionedPthash) {   //2
        {PartitionedPTHashContender<true, pthash::compact_compact>(N, 0.99, 4.0).run();}
        {PartitionedPTHashContender<true, pthash::elias_fano>(N, 0.99, 5.0).run();}
    }

    if (all || most || rest || densePartitionedPtHash) {
        {PhobicContender<pthash::dense_interleaved<pthash::compact>, pthash::table_bucketer<pthash::opt_bucketer>>(N, 1.0, 3.9).run();}   //2
        {PhobicContender<pthash::dense_interleaved<pthash::rice>, pthash::table_bucketer<pthash::opt_bucketer>>(N, 1.0, 4.5).run();}
        {PhobicContender<pthash::dense_interleaved<pthash::rice>, pthash::table_bucketer<pthash::opt_bucketer>>(N, 1.0, 6.5).run();}
        {PhobicContender<pthash::dense_interleaved<pthash::compact>, pthash::table_bucketer<pthash::opt_bucketer>>(N, 1.0, 6.5).run();}
        {PhobicContender<pthash::dense_interleaved<pthash::rice>, pthash::table_bucketer<pthash::opt_bucketer>>(N, 1.0, 9.0).run();}  //2
    }

    if (all || most || rest || rustFmphContender) {   //2
        {RustFmphGoContender(N, 1.0).run();}
        {RustFmphGoContender(N, 2.0).run();}
    }

    if (all || most || rest || rustFmphGoContender) {
        {RustFmphContender(N, 1.0).run();}
        {RustFmphContender(N, 2.0).run();}
    }

    if (all || most || rest || simdrecsplit) {
        {SIMDRecSplitContender<5>(N, 5).run();} 
        {SIMDRecSplitContender<8>(N, 100).run();}
    }

    if (all || sichash || sichash1)
        {SicHashContender<true, 64>(N, 0.97, sichash::SicHashConfig().percentages(0.45, 0.31)).run();}
    if (all || sichash || sichash2)
        {SicHashContender<true, 64>(N, 0.9, sichash::SicHashConfig().percentages(0.21, 0.78)).run();}

    //{ChdContender(N, 1.0, 1.0, 3, true).run();}

    //if (all || bipartiteShockHashFlat)
    //    {BipartiteShockHashFlatContender<64>(N).run();}

    return 0;
}
