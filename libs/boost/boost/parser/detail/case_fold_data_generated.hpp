// Copyright (c) 2024 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Warning: This header is auto-generated (see misc/generate_case_fold_data.py).
// The lack of include guards is intentional.

namespace boost::parser::detail {


struct short_mapping_range {
    char32_t cp_first_;
    char32_t cp_last_;
    uint16_t stride_;
    uint16_t first_idx_;
};
inline constexpr int longest_mapping = 3;
struct long_mapping {
    char32_t cp_;
    char32_t mapping_[longest_mapping + 1];
};
inline constexpr long_mapping  long_mappings[104] = {
    {0x00DF, {0x0073, 0x0073 , 0}},
    {0x0130, {0x0069, 0x0307 , 0}},
    {0x0149, {0x02BC, 0x006E , 0}},
    {0x01F0, {0x006A, 0x030C , 0}},
    {0x0390, {0x03B9, 0x0308, 0x0301 , 0}},
    {0x03B0, {0x03C5, 0x0308, 0x0301 , 0}},
    {0x0587, {0x0565, 0x0582 , 0}},
    {0x1E96, {0x0068, 0x0331 , 0}},
    {0x1E97, {0x0074, 0x0308 , 0}},
    {0x1E98, {0x0077, 0x030A , 0}},
    {0x1E99, {0x0079, 0x030A , 0}},
    {0x1E9A, {0x0061, 0x02BE , 0}},
    {0x1E9E, {0x0073, 0x0073 , 0}},
    {0x1F50, {0x03C5, 0x0313 , 0}},
    {0x1F52, {0x03C5, 0x0313, 0x0300 , 0}},
    {0x1F54, {0x03C5, 0x0313, 0x0301 , 0}},
    {0x1F56, {0x03C5, 0x0313, 0x0342 , 0}},
    {0x1F80, {0x1F00, 0x03B9 , 0}},
    {0x1F81, {0x1F01, 0x03B9 , 0}},
    {0x1F82, {0x1F02, 0x03B9 , 0}},
    {0x1F83, {0x1F03, 0x03B9 , 0}},
    {0x1F84, {0x1F04, 0x03B9 , 0}},
    {0x1F85, {0x1F05, 0x03B9 , 0}},
    {0x1F86, {0x1F06, 0x03B9 , 0}},
    {0x1F87, {0x1F07, 0x03B9 , 0}},
    {0x1F88, {0x1F00, 0x03B9 , 0}},
    {0x1F89, {0x1F01, 0x03B9 , 0}},
    {0x1F8A, {0x1F02, 0x03B9 , 0}},
    {0x1F8B, {0x1F03, 0x03B9 , 0}},
    {0x1F8C, {0x1F04, 0x03B9 , 0}},
    {0x1F8D, {0x1F05, 0x03B9 , 0}},
    {0x1F8E, {0x1F06, 0x03B9 , 0}},
    {0x1F8F, {0x1F07, 0x03B9 , 0}},
    {0x1F90, {0x1F20, 0x03B9 , 0}},
    {0x1F91, {0x1F21, 0x03B9 , 0}},
    {0x1F92, {0x1F22, 0x03B9 , 0}},
    {0x1F93, {0x1F23, 0x03B9 , 0}},
    {0x1F94, {0x1F24, 0x03B9 , 0}},
    {0x1F95, {0x1F25, 0x03B9 , 0}},
    {0x1F96, {0x1F26, 0x03B9 , 0}},
    {0x1F97, {0x1F27, 0x03B9 , 0}},
    {0x1F98, {0x1F20, 0x03B9 , 0}},
    {0x1F99, {0x1F21, 0x03B9 , 0}},
    {0x1F9A, {0x1F22, 0x03B9 , 0}},
    {0x1F9B, {0x1F23, 0x03B9 , 0}},
    {0x1F9C, {0x1F24, 0x03B9 , 0}},
    {0x1F9D, {0x1F25, 0x03B9 , 0}},
    {0x1F9E, {0x1F26, 0x03B9 , 0}},
    {0x1F9F, {0x1F27, 0x03B9 , 0}},
    {0x1FA0, {0x1F60, 0x03B9 , 0}},
    {0x1FA1, {0x1F61, 0x03B9 , 0}},
    {0x1FA2, {0x1F62, 0x03B9 , 0}},
    {0x1FA3, {0x1F63, 0x03B9 , 0}},
    {0x1FA4, {0x1F64, 0x03B9 , 0}},
    {0x1FA5, {0x1F65, 0x03B9 , 0}},
    {0x1FA6, {0x1F66, 0x03B9 , 0}},
    {0x1FA7, {0x1F67, 0x03B9 , 0}},
    {0x1FA8, {0x1F60, 0x03B9 , 0}},
    {0x1FA9, {0x1F61, 0x03B9 , 0}},
    {0x1FAA, {0x1F62, 0x03B9 , 0}},
    {0x1FAB, {0x1F63, 0x03B9 , 0}},
    {0x1FAC, {0x1F64, 0x03B9 , 0}},
    {0x1FAD, {0x1F65, 0x03B9 , 0}},
    {0x1FAE, {0x1F66, 0x03B9 , 0}},
    {0x1FAF, {0x1F67, 0x03B9 , 0}},
    {0x1FB2, {0x1F70, 0x03B9 , 0}},
    {0x1FB3, {0x03B1, 0x03B9 , 0}},
    {0x1FB4, {0x03AC, 0x03B9 , 0}},
    {0x1FB6, {0x03B1, 0x0342 , 0}},
    {0x1FB7, {0x03B1, 0x0342, 0x03B9 , 0}},
    {0x1FBC, {0x03B1, 0x03B9 , 0}},
    {0x1FC2, {0x1F74, 0x03B9 , 0}},
    {0x1FC3, {0x03B7, 0x03B9 , 0}},
    {0x1FC4, {0x03AE, 0x03B9 , 0}},
    {0x1FC6, {0x03B7, 0x0342 , 0}},
    {0x1FC7, {0x03B7, 0x0342, 0x03B9 , 0}},
    {0x1FCC, {0x03B7, 0x03B9 , 0}},
    {0x1FD2, {0x03B9, 0x0308, 0x0300 , 0}},
    {0x1FD3, {0x03B9, 0x0308, 0x0301 , 0}},
    {0x1FD6, {0x03B9, 0x0342 , 0}},
    {0x1FD7, {0x03B9, 0x0308, 0x0342 , 0}},
    {0x1FE2, {0x03C5, 0x0308, 0x0300 , 0}},
    {0x1FE3, {0x03C5, 0x0308, 0x0301 , 0}},
    {0x1FE4, {0x03C1, 0x0313 , 0}},
    {0x1FE6, {0x03C5, 0x0342 , 0}},
    {0x1FE7, {0x03C5, 0x0308, 0x0342 , 0}},
    {0x1FF2, {0x1F7C, 0x03B9 , 0}},
    {0x1FF3, {0x03C9, 0x03B9 , 0}},
    {0x1FF4, {0x03CE, 0x03B9 , 0}},
    {0x1FF6, {0x03C9, 0x0342 , 0}},
    {0x1FF7, {0x03C9, 0x0342, 0x03B9 , 0}},
    {0x1FFC, {0x03C9, 0x03B9 , 0}},
    {0xFB00, {0x0066, 0x0066 , 0}},
    {0xFB01, {0x0066, 0x0069 , 0}},
    {0xFB02, {0x0066, 0x006C , 0}},
    {0xFB03, {0x0066, 0x0066, 0x0069 , 0}},
    {0xFB04, {0x0066, 0x0066, 0x006C , 0}},
    {0xFB05, {0x0073, 0x0074 , 0}},
    {0xFB06, {0x0073, 0x0074 , 0}},
    {0xFB13, {0x0574, 0x0576 , 0}},
    {0xFB14, {0x0574, 0x0565 , 0}},
    {0xFB15, {0x0574, 0x056B , 0}},
    {0xFB16, {0x057E, 0x0576 , 0}},
    {0xFB17, {0x0574, 0x056D , 0}},
};
inline constexpr short_mapping_range mapping_ranges[220] = {
    {0x0041, 0x005A, 1, 0}, 
    {0x005A, 0x00B5, 91, 25}, 
    {0x00B5, 0x00C0, 11, 26}, 
    {0x00C0, 0x00D6, 1, 27}, 
    {0x00D6, 0x00D8, 2, 49}, 
    {0x00D8, 0x00DE, 1, 50}, 
    {0x00DE, 0x0100, 34, 56}, 
    {0x0100, 0x012E, 2, 57}, 
    {0x012E, 0x0132, 4, 80}, 
    {0x0132, 0x0136, 2, 81}, 
    {0x0136, 0x0139, 3, 83}, 
    {0x0139, 0x0147, 2, 84}, 
    {0x0147, 0x014A, 3, 91}, 
    {0x014A, 0x0178, 2, 92}, 
    {0x0178, 0x0179, 1, 115}, 
    {0x0179, 0x0181, 2, 116}, 
    {0x0181, 0x0182, 1, 120}, 
    {0x0182, 0x0186, 2, 121}, 
    {0x0186, 0x0187, 1, 123}, 
    {0x0187, 0x0189, 2, 124}, 
    {0x0189, 0x018B, 1, 125}, 
    {0x018B, 0x018E, 3, 127}, 
    {0x018E, 0x0191, 1, 128}, 
    {0x0191, 0x0193, 2, 131}, 
    {0x0193, 0x0194, 1, 132}, 
    {0x0194, 0x0196, 2, 133}, 
    {0x0196, 0x0198, 1, 134}, 
    {0x0198, 0x019C, 4, 136}, 
    {0x019C, 0x019D, 1, 137}, 
    {0x019D, 0x019F, 2, 138}, 
    {0x019F, 0x01A0, 1, 139}, 
    {0x01A0, 0x01A6, 2, 140}, 
    {0x01A6, 0x01A7, 1, 143}, 
    {0x01A7, 0x01A9, 2, 144}, 
    {0x01A9, 0x01AC, 3, 145}, 
    {0x01AC, 0x01AE, 2, 146}, 
    {0x01AE, 0x01AF, 1, 147}, 
    {0x01AF, 0x01B1, 2, 148}, 
    {0x01B1, 0x01B3, 1, 149}, 
    {0x01B3, 0x01B7, 2, 151}, 
    {0x01B7, 0x01B8, 1, 153}, 
    {0x01B8, 0x01BC, 4, 154}, 
    {0x01BC, 0x01C4, 8, 155}, 
    {0x01C4, 0x01C5, 1, 156}, 
    {0x01C5, 0x01C7, 2, 157}, 
    {0x01C7, 0x01C8, 1, 158}, 
    {0x01C8, 0x01CA, 2, 159}, 
    {0x01CA, 0x01CB, 1, 160}, 
    {0x01CB, 0x01DB, 2, 161}, 
    {0x01DB, 0x01DE, 3, 169}, 
    {0x01DE, 0x01EE, 2, 170}, 
    {0x01EE, 0x01F1, 3, 178}, 
    {0x01F1, 0x01F2, 1, 179}, 
    {0x01F2, 0x01F6, 2, 180}, 
    {0x01F6, 0x01F8, 1, 182}, 
    {0x01F8, 0x0232, 2, 184}, 
    {0x0232, 0x023A, 8, 213}, 
    {0x023A, 0x023B, 1, 214}, 
    {0x023B, 0x023D, 2, 215}, 
    {0x023D, 0x023E, 1, 216}, 
    {0x023E, 0x0241, 3, 217}, 
    {0x0241, 0x0243, 2, 218}, 
    {0x0243, 0x0246, 1, 219}, 
    {0x0246, 0x024E, 2, 222}, 
    {0x024E, 0x0345, 247, 226}, 
    {0x0345, 0x0370, 43, 227}, 
    {0x0370, 0x0372, 2, 228}, 
    {0x0372, 0x0376, 4, 229}, 
    {0x0376, 0x037F, 9, 230}, 
    {0x037F, 0x0386, 7, 231}, 
    {0x0386, 0x0388, 2, 232}, 
    {0x0388, 0x038A, 1, 233}, 
    {0x038A, 0x038E, 2, 235}, 
    {0x038E, 0x038F, 1, 237}, 
    {0x038F, 0x0391, 2, 238}, 
    {0x0391, 0x03A1, 1, 239}, 
    {0x03A1, 0x03A3, 2, 255}, 
    {0x03A3, 0x03AB, 1, 256}, 
    {0x03AB, 0x03C2, 23, 264}, 
    {0x03C2, 0x03CF, 13, 265}, 
    {0x03CF, 0x03D1, 1, 266}, 
    {0x03D1, 0x03D5, 4, 268}, 
    {0x03D5, 0x03D6, 1, 269}, 
    {0x03D6, 0x03F0, 2, 270}, 
    {0x03F0, 0x03F1, 1, 283}, 
    {0x03F1, 0x03F4, 3, 284}, 
    {0x03F4, 0x03F5, 1, 285}, 
    {0x03F5, 0x03F9, 2, 286}, 
    {0x03F9, 0x03FA, 1, 288}, 
    {0x03FA, 0x03FD, 3, 289}, 
    {0x03FD, 0x042F, 1, 290}, 
    {0x042F, 0x0460, 49, 340}, 
    {0x0460, 0x0480, 2, 341}, 
    {0x0480, 0x048A, 10, 357}, 
    {0x048A, 0x04C0, 2, 358}, 
    {0x04C0, 0x04C1, 1, 385}, 
    {0x04C1, 0x04CD, 2, 386}, 
    {0x04CD, 0x04D0, 3, 392}, 
    {0x04D0, 0x052E, 2, 393}, 
    {0x052E, 0x0531, 3, 440}, 
    {0x0531, 0x0556, 1, 441}, 
    {0x0556, 0x10A0, 2890, 478}, 
    {0x10A0, 0x10C5, 1, 479}, 
    {0x10C5, 0x10C7, 2, 516}, 
    {0x10C7, 0x10CD, 6, 517}, 
    {0x10CD, 0x13F8, 811, 518}, 
    {0x13F8, 0x13FD, 1, 519}, 
    {0x13FD, 0x1C80, 2179, 524}, 
    {0x1C80, 0x1C88, 1, 525}, 
    {0x1C88, 0x1C90, 8, 533}, 
    {0x1C90, 0x1CBA, 1, 534}, 
    {0x1CBA, 0x1CBD, 3, 576}, 
    {0x1CBD, 0x1CBF, 1, 577}, 
    {0x1CBF, 0x1E00, 321, 579}, 
    {0x1E00, 0x1E94, 2, 580}, 
    {0x1E94, 0x1E9B, 7, 654}, 
    {0x1E9B, 0x1EA0, 5, 655}, 
    {0x1EA0, 0x1EFE, 2, 656}, 
    {0x1EFE, 0x1F08, 10, 703}, 
    {0x1F08, 0x1F0F, 1, 704}, 
    {0x1F0F, 0x1F18, 9, 711}, 
    {0x1F18, 0x1F1D, 1, 712}, 
    {0x1F1D, 0x1F28, 11, 717}, 
    {0x1F28, 0x1F2F, 1, 718}, 
    {0x1F2F, 0x1F38, 9, 725}, 
    {0x1F38, 0x1F3F, 1, 726}, 
    {0x1F3F, 0x1F48, 9, 733}, 
    {0x1F48, 0x1F4D, 1, 734}, 
    {0x1F4D, 0x1F59, 12, 739}, 
    {0x1F59, 0x1F5F, 2, 740}, 
    {0x1F5F, 0x1F68, 9, 743}, 
    {0x1F68, 0x1F6F, 1, 744}, 
    {0x1F6F, 0x1FB8, 73, 751}, 
    {0x1FB8, 0x1FBB, 1, 752}, 
    {0x1FBB, 0x1FBE, 3, 755}, 
    {0x1FBE, 0x1FC8, 10, 756}, 
    {0x1FC8, 0x1FCB, 1, 757}, 
    {0x1FCB, 0x1FD8, 13, 760}, 
    {0x1FD8, 0x1FDB, 1, 761}, 
    {0x1FDB, 0x1FE8, 13, 764}, 
    {0x1FE8, 0x1FEC, 1, 765}, 
    {0x1FEC, 0x1FF8, 12, 769}, 
    {0x1FF8, 0x1FFB, 1, 770}, 
    {0x1FFB, 0x2126, 299, 773}, 
    {0x2126, 0x212A, 4, 774}, 
    {0x212A, 0x212B, 1, 775}, 
    {0x212B, 0x2132, 7, 776}, 
    {0x2132, 0x2160, 46, 777}, 
    {0x2160, 0x216F, 1, 778}, 
    {0x216F, 0x2183, 20, 793}, 
    {0x2183, 0x24B6, 819, 794}, 
    {0x24B6, 0x24CF, 1, 795}, 
    {0x24CF, 0x2C00, 1841, 820}, 
    {0x2C00, 0x2C2F, 1, 821}, 
    {0x2C2F, 0x2C60, 49, 868}, 
    {0x2C60, 0x2C62, 2, 869}, 
    {0x2C62, 0x2C64, 1, 870}, 
    {0x2C64, 0x2C67, 3, 872}, 
    {0x2C67, 0x2C6D, 2, 873}, 
    {0x2C6D, 0x2C70, 1, 876}, 
    {0x2C70, 0x2C72, 2, 879}, 
    {0x2C72, 0x2C75, 3, 880}, 
    {0x2C75, 0x2C7E, 9, 881}, 
    {0x2C7E, 0x2C80, 1, 882}, 
    {0x2C80, 0x2CE2, 2, 884}, 
    {0x2CE2, 0x2CEB, 9, 933}, 
    {0x2CEB, 0x2CED, 2, 934}, 
    {0x2CED, 0x2CF2, 5, 935}, 
    {0x2CF2, 0xA640, 31054, 936}, 
    {0xA640, 0xA66C, 2, 937}, 
    {0xA66C, 0xA680, 20, 959}, 
    {0xA680, 0xA69A, 2, 960}, 
    {0xA69A, 0xA722, 136, 973}, 
    {0xA722, 0xA72E, 2, 974}, 
    {0xA72E, 0xA732, 4, 980}, 
    {0xA732, 0xA76E, 2, 981}, 
    {0xA76E, 0xA779, 11, 1011}, 
    {0xA779, 0xA77D, 2, 1012}, 
    {0xA77D, 0xA77E, 1, 1014}, 
    {0xA77E, 0xA786, 2, 1015}, 
    {0xA786, 0xA78B, 5, 1019}, 
    {0xA78B, 0xA78D, 2, 1020}, 
    {0xA78D, 0xA790, 3, 1021}, 
    {0xA790, 0xA792, 2, 1022}, 
    {0xA792, 0xA796, 4, 1023}, 
    {0xA796, 0xA7AA, 2, 1024}, 
    {0xA7AA, 0xA7AE, 1, 1034}, 
    {0xA7AE, 0xA7B0, 2, 1038}, 
    {0xA7B0, 0xA7B4, 1, 1039}, 
    {0xA7B4, 0xA7C4, 2, 1043}, 
    {0xA7C4, 0xA7C7, 1, 1051}, 
    {0xA7C7, 0xA7C9, 2, 1054}, 
    {0xA7C9, 0xA7D0, 7, 1055}, 
    {0xA7D0, 0xA7D6, 6, 1056}, 
    {0xA7D6, 0xA7D8, 2, 1057}, 
    {0xA7D8, 0xA7F5, 29, 1058}, 
    {0xA7F5, 0xAB70, 891, 1059}, 
    {0xAB70, 0xABBF, 1, 1060}, 
    {0xABBF, 0xFF21, 21346, 1139}, 
    {0xFF21, 0xFF3A, 1, 1140}, 
    {0xFF3A, 0x10400, 1222, 1165}, 
    {0x10400, 0x10427, 1, 1166}, 
    {0x10427, 0x104B0, 137, 1205}, 
    {0x104B0, 0x104D3, 1, 1206}, 
    {0x104D3, 0x10570, 157, 1241}, 
    {0x10570, 0x1057A, 1, 1242}, 
    {0x1057A, 0x1057C, 2, 1252}, 
    {0x1057C, 0x1058A, 1, 1253}, 
    {0x1058A, 0x1058C, 2, 1267}, 
    {0x1058C, 0x10592, 1, 1268}, 
    {0x10592, 0x10594, 2, 1274}, 
    {0x10594, 0x10595, 1, 1275}, 
    {0x10595, 0x10C80, 1771, 1276}, 
    {0x10C80, 0x10CB2, 1, 1277}, 
    {0x10CB2, 0x118A0, 3054, 1327}, 
    {0x118A0, 0x118BF, 1, 1328}, 
    {0x118BF, 0x16E40, 21889, 1359}, 
    {0x16E40, 0x16E5F, 1, 1360}, 
    {0x16E5F, 0x1E900, 31393, 1391}, 
    {0x1E900, 0x1E921 + 1, 1, 1392}, 
};
inline constexpr char32_t single_mapping_cps[1426] = {
    0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 
    0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F, 0x0070, 
    0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 
    0x0079, 0x007A, 0x03BC, 0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 
    0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 
    0x00ED, 0x00EE, 0x00EF, 0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 
    0x00F5, 0x00F6, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 
    0x00FE, 0x0101, 0x0103, 0x0105, 0x0107, 0x0109, 0x010B, 0x010D, 
    0x010F, 0x0111, 0x0113, 0x0115, 0x0117, 0x0119, 0x011B, 0x011D, 
    0x011F, 0x0121, 0x0123, 0x0125, 0x0127, 0x0129, 0x012B, 0x012D, 
    0x012F, 0x0133, 0x0135, 0x0137, 0x013A, 0x013C, 0x013E, 0x0140, 
    0x0142, 0x0144, 0x0146, 0x0148, 0x014B, 0x014D, 0x014F, 0x0151, 
    0x0153, 0x0155, 0x0157, 0x0159, 0x015B, 0x015D, 0x015F, 0x0161, 
    0x0163, 0x0165, 0x0167, 0x0169, 0x016B, 0x016D, 0x016F, 0x0171, 
    0x0173, 0x0175, 0x0177, 0x00FF, 0x017A, 0x017C, 0x017E, 0x0073, 
    0x0253, 0x0183, 0x0185, 0x0254, 0x0188, 0x0256, 0x0257, 0x018C, 
    0x01DD, 0x0259, 0x025B, 0x0192, 0x0260, 0x0263, 0x0269, 0x0268, 
    0x0199, 0x026F, 0x0272, 0x0275, 0x01A1, 0x01A3, 0x01A5, 0x0280, 
    0x01A8, 0x0283, 0x01AD, 0x0288, 0x01B0, 0x028A, 0x028B, 0x01B4, 
    0x01B6, 0x0292, 0x01B9, 0x01BD, 0x01C6, 0x01C6, 0x01C9, 0x01C9, 
    0x01CC, 0x01CC, 0x01CE, 0x01D0, 0x01D2, 0x01D4, 0x01D6, 0x01D8, 
    0x01DA, 0x01DC, 0x01DF, 0x01E1, 0x01E3, 0x01E5, 0x01E7, 0x01E9, 
    0x01EB, 0x01ED, 0x01EF, 0x01F3, 0x01F3, 0x01F5, 0x0195, 0x01BF, 
    0x01F9, 0x01FB, 0x01FD, 0x01FF, 0x0201, 0x0203, 0x0205, 0x0207, 
    0x0209, 0x020B, 0x020D, 0x020F, 0x0211, 0x0213, 0x0215, 0x0217, 
    0x0219, 0x021B, 0x021D, 0x021F, 0x019E, 0x0223, 0x0225, 0x0227, 
    0x0229, 0x022B, 0x022D, 0x022F, 0x0231, 0x0233, 0x2C65, 0x023C, 
    0x019A, 0x2C66, 0x0242, 0x0180, 0x0289, 0x028C, 0x0247, 0x0249, 
    0x024B, 0x024D, 0x024F, 0x03B9, 0x0371, 0x0373, 0x0377, 0x03F3, 
    0x03AC, 0x03AD, 0x03AE, 0x03AF, 0x03CC, 0x03CD, 0x03CE, 0x03B1, 
    0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6, 0x03B7, 0x03B8, 0x03B9, 
    0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE, 0x03BF, 0x03C0, 0x03C1, 
    0x03C3, 0x03C4, 0x03C5, 0x03C6, 0x03C7, 0x03C8, 0x03C9, 0x03CA, 
    0x03CB, 0x03C3, 0x03D7, 0x03B2, 0x03B8, 0x03C6, 0x03C0, 0x03D9, 
    0x03DB, 0x03DD, 0x03DF, 0x03E1, 0x03E3, 0x03E5, 0x03E7, 0x03E9, 
    0x03EB, 0x03ED, 0x03EF, 0x03BA, 0x03C1, 0x03B8, 0x03B5, 0x03F8, 
    0x03F2, 0x03FB, 0x037B, 0x037C, 0x037D, 0x0450, 0x0451, 0x0452, 
    0x0453, 0x0454, 0x0455, 0x0456, 0x0457, 0x0458, 0x0459, 0x045A, 
    0x045B, 0x045C, 0x045D, 0x045E, 0x045F, 0x0430, 0x0431, 0x0432, 
    0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 0x0438, 0x0439, 0x043A, 
    0x043B, 0x043C, 0x043D, 0x043E, 0x043F, 0x0440, 0x0441, 0x0442, 
    0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 0x0448, 0x0449, 0x044A, 
    0x044B, 0x044C, 0x044D, 0x044E, 0x044F, 0x0461, 0x0463, 0x0465, 
    0x0467, 0x0469, 0x046B, 0x046D, 0x046F, 0x0471, 0x0473, 0x0475, 
    0x0477, 0x0479, 0x047B, 0x047D, 0x047F, 0x0481, 0x048B, 0x048D, 
    0x048F, 0x0491, 0x0493, 0x0495, 0x0497, 0x0499, 0x049B, 0x049D, 
    0x049F, 0x04A1, 0x04A3, 0x04A5, 0x04A7, 0x04A9, 0x04AB, 0x04AD, 
    0x04AF, 0x04B1, 0x04B3, 0x04B5, 0x04B7, 0x04B9, 0x04BB, 0x04BD, 
    0x04BF, 0x04CF, 0x04C2, 0x04C4, 0x04C6, 0x04C8, 0x04CA, 0x04CC, 
    0x04CE, 0x04D1, 0x04D3, 0x04D5, 0x04D7, 0x04D9, 0x04DB, 0x04DD, 
    0x04DF, 0x04E1, 0x04E3, 0x04E5, 0x04E7, 0x04E9, 0x04EB, 0x04ED, 
    0x04EF, 0x04F1, 0x04F3, 0x04F5, 0x04F7, 0x04F9, 0x04FB, 0x04FD, 
    0x04FF, 0x0501, 0x0503, 0x0505, 0x0507, 0x0509, 0x050B, 0x050D, 
    0x050F, 0x0511, 0x0513, 0x0515, 0x0517, 0x0519, 0x051B, 0x051D, 
    0x051F, 0x0521, 0x0523, 0x0525, 0x0527, 0x0529, 0x052B, 0x052D, 
    0x052F, 0x0561, 0x0562, 0x0563, 0x0564, 0x0565, 0x0566, 0x0567, 
    0x0568, 0x0569, 0x056A, 0x056B, 0x056C, 0x056D, 0x056E, 0x056F, 
    0x0570, 0x0571, 0x0572, 0x0573, 0x0574, 0x0575, 0x0576, 0x0577, 
    0x0578, 0x0579, 0x057A, 0x057B, 0x057C, 0x057D, 0x057E, 0x057F, 
    0x0580, 0x0581, 0x0582, 0x0583, 0x0584, 0x0585, 0x0586, 0x2D00, 
    0x2D01, 0x2D02, 0x2D03, 0x2D04, 0x2D05, 0x2D06, 0x2D07, 0x2D08, 
    0x2D09, 0x2D0A, 0x2D0B, 0x2D0C, 0x2D0D, 0x2D0E, 0x2D0F, 0x2D10, 
    0x2D11, 0x2D12, 0x2D13, 0x2D14, 0x2D15, 0x2D16, 0x2D17, 0x2D18, 
    0x2D19, 0x2D1A, 0x2D1B, 0x2D1C, 0x2D1D, 0x2D1E, 0x2D1F, 0x2D20, 
    0x2D21, 0x2D22, 0x2D23, 0x2D24, 0x2D25, 0x2D27, 0x2D2D, 0x13F0, 
    0x13F1, 0x13F2, 0x13F3, 0x13F4, 0x13F5, 0x0432, 0x0434, 0x043E, 
    0x0441, 0x0442, 0x0442, 0x044A, 0x0463, 0xA64B, 0x10D0, 0x10D1, 
    0x10D2, 0x10D3, 0x10D4, 0x10D5, 0x10D6, 0x10D7, 0x10D8, 0x10D9, 
    0x10DA, 0x10DB, 0x10DC, 0x10DD, 0x10DE, 0x10DF, 0x10E0, 0x10E1, 
    0x10E2, 0x10E3, 0x10E4, 0x10E5, 0x10E6, 0x10E7, 0x10E8, 0x10E9, 
    0x10EA, 0x10EB, 0x10EC, 0x10ED, 0x10EE, 0x10EF, 0x10F0, 0x10F1, 
    0x10F2, 0x10F3, 0x10F4, 0x10F5, 0x10F6, 0x10F7, 0x10F8, 0x10F9, 
    0x10FA, 0x10FD, 0x10FE, 0x10FF, 0x1E01, 0x1E03, 0x1E05, 0x1E07, 
    0x1E09, 0x1E0B, 0x1E0D, 0x1E0F, 0x1E11, 0x1E13, 0x1E15, 0x1E17, 
    0x1E19, 0x1E1B, 0x1E1D, 0x1E1F, 0x1E21, 0x1E23, 0x1E25, 0x1E27, 
    0x1E29, 0x1E2B, 0x1E2D, 0x1E2F, 0x1E31, 0x1E33, 0x1E35, 0x1E37, 
    0x1E39, 0x1E3B, 0x1E3D, 0x1E3F, 0x1E41, 0x1E43, 0x1E45, 0x1E47, 
    0x1E49, 0x1E4B, 0x1E4D, 0x1E4F, 0x1E51, 0x1E53, 0x1E55, 0x1E57, 
    0x1E59, 0x1E5B, 0x1E5D, 0x1E5F, 0x1E61, 0x1E63, 0x1E65, 0x1E67, 
    0x1E69, 0x1E6B, 0x1E6D, 0x1E6F, 0x1E71, 0x1E73, 0x1E75, 0x1E77, 
    0x1E79, 0x1E7B, 0x1E7D, 0x1E7F, 0x1E81, 0x1E83, 0x1E85, 0x1E87, 
    0x1E89, 0x1E8B, 0x1E8D, 0x1E8F, 0x1E91, 0x1E93, 0x1E95, 0x1E61, 
    0x1EA1, 0x1EA3, 0x1EA5, 0x1EA7, 0x1EA9, 0x1EAB, 0x1EAD, 0x1EAF, 
    0x1EB1, 0x1EB3, 0x1EB5, 0x1EB7, 0x1EB9, 0x1EBB, 0x1EBD, 0x1EBF, 
    0x1EC1, 0x1EC3, 0x1EC5, 0x1EC7, 0x1EC9, 0x1ECB, 0x1ECD, 0x1ECF, 
    0x1ED1, 0x1ED3, 0x1ED5, 0x1ED7, 0x1ED9, 0x1EDB, 0x1EDD, 0x1EDF, 
    0x1EE1, 0x1EE3, 0x1EE5, 0x1EE7, 0x1EE9, 0x1EEB, 0x1EED, 0x1EEF, 
    0x1EF1, 0x1EF3, 0x1EF5, 0x1EF7, 0x1EF9, 0x1EFB, 0x1EFD, 0x1EFF, 
    0x1F00, 0x1F01, 0x1F02, 0x1F03, 0x1F04, 0x1F05, 0x1F06, 0x1F07, 
    0x1F10, 0x1F11, 0x1F12, 0x1F13, 0x1F14, 0x1F15, 0x1F20, 0x1F21, 
    0x1F22, 0x1F23, 0x1F24, 0x1F25, 0x1F26, 0x1F27, 0x1F30, 0x1F31, 
    0x1F32, 0x1F33, 0x1F34, 0x1F35, 0x1F36, 0x1F37, 0x1F40, 0x1F41, 
    0x1F42, 0x1F43, 0x1F44, 0x1F45, 0x1F51, 0x1F53, 0x1F55, 0x1F57, 
    0x1F60, 0x1F61, 0x1F62, 0x1F63, 0x1F64, 0x1F65, 0x1F66, 0x1F67, 
    0x1FB0, 0x1FB1, 0x1F70, 0x1F71, 0x03B9, 0x1F72, 0x1F73, 0x1F74, 
    0x1F75, 0x1FD0, 0x1FD1, 0x1F76, 0x1F77, 0x1FE0, 0x1FE1, 0x1F7A, 
    0x1F7B, 0x1FE5, 0x1F78, 0x1F79, 0x1F7C, 0x1F7D, 0x03C9, 0x006B, 
    0x00E5, 0x214E, 0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0x2175, 
    0x2176, 0x2177, 0x2178, 0x2179, 0x217A, 0x217B, 0x217C, 0x217D, 
    0x217E, 0x217F, 0x2184, 0x24D0, 0x24D1, 0x24D2, 0x24D3, 0x24D4, 
    0x24D5, 0x24D6, 0x24D7, 0x24D8, 0x24D9, 0x24DA, 0x24DB, 0x24DC, 
    0x24DD, 0x24DE, 0x24DF, 0x24E0, 0x24E1, 0x24E2, 0x24E3, 0x24E4, 
    0x24E5, 0x24E6, 0x24E7, 0x24E8, 0x24E9, 0x2C30, 0x2C31, 0x2C32, 
    0x2C33, 0x2C34, 0x2C35, 0x2C36, 0x2C37, 0x2C38, 0x2C39, 0x2C3A, 
    0x2C3B, 0x2C3C, 0x2C3D, 0x2C3E, 0x2C3F, 0x2C40, 0x2C41, 0x2C42, 
    0x2C43, 0x2C44, 0x2C45, 0x2C46, 0x2C47, 0x2C48, 0x2C49, 0x2C4A, 
    0x2C4B, 0x2C4C, 0x2C4D, 0x2C4E, 0x2C4F, 0x2C50, 0x2C51, 0x2C52, 
    0x2C53, 0x2C54, 0x2C55, 0x2C56, 0x2C57, 0x2C58, 0x2C59, 0x2C5A, 
    0x2C5B, 0x2C5C, 0x2C5D, 0x2C5E, 0x2C5F, 0x2C61, 0x026B, 0x1D7D, 
    0x027D, 0x2C68, 0x2C6A, 0x2C6C, 0x0251, 0x0271, 0x0250, 0x0252, 
    0x2C73, 0x2C76, 0x023F, 0x0240, 0x2C81, 0x2C83, 0x2C85, 0x2C87, 
    0x2C89, 0x2C8B, 0x2C8D, 0x2C8F, 0x2C91, 0x2C93, 0x2C95, 0x2C97, 
    0x2C99, 0x2C9B, 0x2C9D, 0x2C9F, 0x2CA1, 0x2CA3, 0x2CA5, 0x2CA7, 
    0x2CA9, 0x2CAB, 0x2CAD, 0x2CAF, 0x2CB1, 0x2CB3, 0x2CB5, 0x2CB7, 
    0x2CB9, 0x2CBB, 0x2CBD, 0x2CBF, 0x2CC1, 0x2CC3, 0x2CC5, 0x2CC7, 
    0x2CC9, 0x2CCB, 0x2CCD, 0x2CCF, 0x2CD1, 0x2CD3, 0x2CD5, 0x2CD7, 
    0x2CD9, 0x2CDB, 0x2CDD, 0x2CDF, 0x2CE1, 0x2CE3, 0x2CEC, 0x2CEE, 
    0x2CF3, 0xA641, 0xA643, 0xA645, 0xA647, 0xA649, 0xA64B, 0xA64D, 
    0xA64F, 0xA651, 0xA653, 0xA655, 0xA657, 0xA659, 0xA65B, 0xA65D, 
    0xA65F, 0xA661, 0xA663, 0xA665, 0xA667, 0xA669, 0xA66B, 0xA66D, 
    0xA681, 0xA683, 0xA685, 0xA687, 0xA689, 0xA68B, 0xA68D, 0xA68F, 
    0xA691, 0xA693, 0xA695, 0xA697, 0xA699, 0xA69B, 0xA723, 0xA725, 
    0xA727, 0xA729, 0xA72B, 0xA72D, 0xA72F, 0xA733, 0xA735, 0xA737, 
    0xA739, 0xA73B, 0xA73D, 0xA73F, 0xA741, 0xA743, 0xA745, 0xA747, 
    0xA749, 0xA74B, 0xA74D, 0xA74F, 0xA751, 0xA753, 0xA755, 0xA757, 
    0xA759, 0xA75B, 0xA75D, 0xA75F, 0xA761, 0xA763, 0xA765, 0xA767, 
    0xA769, 0xA76B, 0xA76D, 0xA76F, 0xA77A, 0xA77C, 0x1D79, 0xA77F, 
    0xA781, 0xA783, 0xA785, 0xA787, 0xA78C, 0x0265, 0xA791, 0xA793, 
    0xA797, 0xA799, 0xA79B, 0xA79D, 0xA79F, 0xA7A1, 0xA7A3, 0xA7A5, 
    0xA7A7, 0xA7A9, 0x0266, 0x025C, 0x0261, 0x026C, 0x026A, 0x029E, 
    0x0287, 0x029D, 0xAB53, 0xA7B5, 0xA7B7, 0xA7B9, 0xA7BB, 0xA7BD, 
    0xA7BF, 0xA7C1, 0xA7C3, 0xA794, 0x0282, 0x1D8E, 0xA7C8, 0xA7CA, 
    0xA7D1, 0xA7D7, 0xA7D9, 0xA7F6, 0x13A0, 0x13A1, 0x13A2, 0x13A3, 
    0x13A4, 0x13A5, 0x13A6, 0x13A7, 0x13A8, 0x13A9, 0x13AA, 0x13AB, 
    0x13AC, 0x13AD, 0x13AE, 0x13AF, 0x13B0, 0x13B1, 0x13B2, 0x13B3, 
    0x13B4, 0x13B5, 0x13B6, 0x13B7, 0x13B8, 0x13B9, 0x13BA, 0x13BB, 
    0x13BC, 0x13BD, 0x13BE, 0x13BF, 0x13C0, 0x13C1, 0x13C2, 0x13C3, 
    0x13C4, 0x13C5, 0x13C6, 0x13C7, 0x13C8, 0x13C9, 0x13CA, 0x13CB, 
    0x13CC, 0x13CD, 0x13CE, 0x13CF, 0x13D0, 0x13D1, 0x13D2, 0x13D3, 
    0x13D4, 0x13D5, 0x13D6, 0x13D7, 0x13D8, 0x13D9, 0x13DA, 0x13DB, 
    0x13DC, 0x13DD, 0x13DE, 0x13DF, 0x13E0, 0x13E1, 0x13E2, 0x13E3, 
    0x13E4, 0x13E5, 0x13E6, 0x13E7, 0x13E8, 0x13E9, 0x13EA, 0x13EB, 
    0x13EC, 0x13ED, 0x13EE, 0x13EF, 0xFF41, 0xFF42, 0xFF43, 0xFF44, 
    0xFF45, 0xFF46, 0xFF47, 0xFF48, 0xFF49, 0xFF4A, 0xFF4B, 0xFF4C, 
    0xFF4D, 0xFF4E, 0xFF4F, 0xFF50, 0xFF51, 0xFF52, 0xFF53, 0xFF54, 
    0xFF55, 0xFF56, 0xFF57, 0xFF58, 0xFF59, 0xFF5A, 0x10428, 0x10429, 
    0x1042A, 0x1042B, 0x1042C, 0x1042D, 0x1042E, 0x1042F, 0x10430, 0x10431, 
    0x10432, 0x10433, 0x10434, 0x10435, 0x10436, 0x10437, 0x10438, 0x10439, 
    0x1043A, 0x1043B, 0x1043C, 0x1043D, 0x1043E, 0x1043F, 0x10440, 0x10441, 
    0x10442, 0x10443, 0x10444, 0x10445, 0x10446, 0x10447, 0x10448, 0x10449, 
    0x1044A, 0x1044B, 0x1044C, 0x1044D, 0x1044E, 0x1044F, 0x104D8, 0x104D9, 
    0x104DA, 0x104DB, 0x104DC, 0x104DD, 0x104DE, 0x104DF, 0x104E0, 0x104E1, 
    0x104E2, 0x104E3, 0x104E4, 0x104E5, 0x104E6, 0x104E7, 0x104E8, 0x104E9, 
    0x104EA, 0x104EB, 0x104EC, 0x104ED, 0x104EE, 0x104EF, 0x104F0, 0x104F1, 
    0x104F2, 0x104F3, 0x104F4, 0x104F5, 0x104F6, 0x104F7, 0x104F8, 0x104F9, 
    0x104FA, 0x104FB, 0x10597, 0x10598, 0x10599, 0x1059A, 0x1059B, 0x1059C, 
    0x1059D, 0x1059E, 0x1059F, 0x105A0, 0x105A1, 0x105A3, 0x105A4, 0x105A5, 
    0x105A6, 0x105A7, 0x105A8, 0x105A9, 0x105AA, 0x105AB, 0x105AC, 0x105AD, 
    0x105AE, 0x105AF, 0x105B0, 0x105B1, 0x105B3, 0x105B4, 0x105B5, 0x105B6, 
    0x105B7, 0x105B8, 0x105B9, 0x105BB, 0x105BC, 0x10CC0, 0x10CC1, 0x10CC2, 
    0x10CC3, 0x10CC4, 0x10CC5, 0x10CC6, 0x10CC7, 0x10CC8, 0x10CC9, 0x10CCA, 
    0x10CCB, 0x10CCC, 0x10CCD, 0x10CCE, 0x10CCF, 0x10CD0, 0x10CD1, 0x10CD2, 
    0x10CD3, 0x10CD4, 0x10CD5, 0x10CD6, 0x10CD7, 0x10CD8, 0x10CD9, 0x10CDA, 
    0x10CDB, 0x10CDC, 0x10CDD, 0x10CDE, 0x10CDF, 0x10CE0, 0x10CE1, 0x10CE2, 
    0x10CE3, 0x10CE4, 0x10CE5, 0x10CE6, 0x10CE7, 0x10CE8, 0x10CE9, 0x10CEA, 
    0x10CEB, 0x10CEC, 0x10CED, 0x10CEE, 0x10CEF, 0x10CF0, 0x10CF1, 0x10CF2, 
    0x118C0, 0x118C1, 0x118C2, 0x118C3, 0x118C4, 0x118C5, 0x118C6, 0x118C7, 
    0x118C8, 0x118C9, 0x118CA, 0x118CB, 0x118CC, 0x118CD, 0x118CE, 0x118CF, 
    0x118D0, 0x118D1, 0x118D2, 0x118D3, 0x118D4, 0x118D5, 0x118D6, 0x118D7, 
    0x118D8, 0x118D9, 0x118DA, 0x118DB, 0x118DC, 0x118DD, 0x118DE, 0x118DF, 
    0x16E60, 0x16E61, 0x16E62, 0x16E63, 0x16E64, 0x16E65, 0x16E66, 0x16E67, 
    0x16E68, 0x16E69, 0x16E6A, 0x16E6B, 0x16E6C, 0x16E6D, 0x16E6E, 0x16E6F, 
    0x16E70, 0x16E71, 0x16E72, 0x16E73, 0x16E74, 0x16E75, 0x16E76, 0x16E77, 
    0x16E78, 0x16E79, 0x16E7A, 0x16E7B, 0x16E7C, 0x16E7D, 0x16E7E, 0x16E7F, 
    0x1E922, 0x1E923, 0x1E924, 0x1E925, 0x1E926, 0x1E927, 0x1E928, 0x1E929, 
    0x1E92A, 0x1E92B, 0x1E92C, 0x1E92D, 0x1E92E, 0x1E92F, 0x1E930, 0x1E931, 
    0x1E932, 0x1E933, 0x1E934, 0x1E935, 0x1E936, 0x1E937, 0x1E938, 0x1E939, 
    0x1E93A, 0x1E93B, 0x1E93C, 0x1E93D, 0x1E93E, 0x1E93F, 0x1E940, 0x1E941, 
    0x1E942, 0x1E943, 
};

}
