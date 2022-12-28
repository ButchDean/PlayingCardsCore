//
// Created by Dean Butcher on 2021-10-24.
//

#include <cstdio>
#include <string>

typedef unsigned int uint;

constexpr uint TOTAL_BAR_LENGTH = 30;

bool UpdateProgress(uint pct, const uint size) {
    const uint BARCOUNT = (pct + 1) * TOTAL_BAR_LENGTH / 100;

    auto printSegment = [](std::string&& s) {
        std::printf("%s", s.c_str());
    };

    std::printf("\rShuffling Deck: [");

    for(uint i = 0; i < BARCOUNT; i++) {
        printSegment("=");
    }

    uint BLANK_COUNT = TOTAL_BAR_LENGTH - BARCOUNT;

    for(uint j = 0; j < BLANK_COUNT; j++) {
        printSegment(" ");
    }

    std::printf("] %d%% for %d cards", (pct == 0 ? 0 : pct + 1), size);

    std::fflush(stdout);

    return true;
}