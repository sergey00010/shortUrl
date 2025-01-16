// Copyright John Maddock 2019.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef SC_
#  define SC_(x) static_cast<T>(BOOST_JOIN(x, L))
#endif
   static const std::array<std::array<T, 4>, 7> hypergeometric_1F1_big_double_limited = {{
      { SC_(-9.6886797109618782997131347656250000000000e-06), SC_(-1.2525131835937500000000000000000000000000e+03), SC_(-1.0437607421875000000000000000000000000000e+03), SC_(9.9998253928322852691286461253432557187618e-01) },
      { SC_(9.6886760729830712080001831054687500000000e-06), SC_(-1.2525131835937500000000000000000000000000e+03), SC_(-1.0437607421875000000000000000000000000000e+03), SC_(1.0000174610171120995494972331285845784973e+00) },
      { SC_(-9.1337614555042634378878574352711439132690e-13), SC_(-1.2525131835937500000000000000000000000000e+03), SC_(-1.0437607421875000000000000000000000000000e+03), SC_(9.9999999999835391995458077011747081732328e-01) },
      { SC_(9.1337571186955734958701214054599404335022e-13), SC_(-1.2525131835937500000000000000000000000000e+03), SC_(-1.0437607421875000000000000000000000000000e+03), SC_(1.0000000000016460792638453549919301101979e+00) },
      { { static_cast<T>(std::ldexp((double)10485392221989376, -40)), static_cast<T>(std::ldexp((double)-11440692920695040, -40)), static_cast<T>(std::ldexp((double)15790527852544000, -44)), SC_(1.18289892801537469540400591236035802241505227e+161) } },
      { { static_cast<T>(std::ldexp((double)10485980564770816, -40)), static_cast<T>(std::ldexp((double)-10424015334037760, -40)), static_cast<T>(std::ldexp((double)12850940076032000, -44)), SC_(-5.63691240015269602721075116789607623755153984e-99) } },
      { { static_cast<T>(std::ldexp((double)10485102088130304, -40)), static_cast<T>(std::ldexp((double)-12174307949802496, -40)), static_cast<T>(std::ldexp((double)17027372515328000, -44)), SC_(-619367491691927041975872.474550388407917992627) } },
   }};
//#undef SC_

