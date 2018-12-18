#include <bits/stdc++.h>
using namespace std;

const int N = 1500000000;

char counters[N/4 + 1];

namespace CacheOptimization {
const int MAGIC = 170000;
const int LPARTITION = 8;
const int MSBS = 30 - LPARTITION;
const int PARTITION = (N >> MSBS + 1) + 1;

int cur[PARTITION];
int tmp[PARTITION][MAGIC];

inline void add(int p) {
    int idx = p >> MSBS;
    tmp[idx][cur[idx]++] = p;

    if (cur[idx] == MAGIC) {
        for (int i=0; i<MAGIC; i++) counters[tmp[idx][i] >> 1] += 1 << ((tmp[idx][i] & 1) << 2);
        cur[idx] = 0;
    }
}

inline void update_all() {
    for (int i=0; i<PARTITION; i++) {
        for (int j=0; j<cur[i]; ++j) {
            counters[tmp[i][j] >> 1] += 1 << ((tmp[i][j] & 1) << 2);
        }
        cur[i] = 0;
    }    
}
}

void generate_triangles() {
    int sz;
    int st[8000][3];

    st[0][0] = st[0][1] = 2; st[0][2] = 3;
    sz = 1;
    
    while (sz) {
        --sz;
        int a = st[sz][0], b = st[sz][1], c = st[sz][2];
        
        CacheOptimization::add(st[sz][0] + st[sz][1] + st[sz][2] >> 1);
        
        long long a5 = 5LL*a, b5 = 5LL*b, c7 = 7LL*c;
        int c3 = c*3;
        
        if (a5 - b5 + c7 <= N) {
            st[sz][0] = a - b*2 + c*2, st[sz][1] = a*2 - b + c*2, st[sz][2] = a*2 - 2*b + c3;
            ++sz;
        }
        
        if (a5 + b5 + c7 <= N) {
            st[sz][0] = a + b*2 + c*2, st[sz][1] = a*2 + b + c*2, st[sz][2] = a*2 + b*2 + c3;
            ++sz;
        } 
        
        if (-a5 + b5 + c7 <= N && a != b) {
            st[sz][0] = -a + b*2 + c*2, st[sz][1] = -a*2 + b + c*2, st[sz][2] = -a*2 + 2*b + c3;
            ++sz;
        }
    }
    
    CacheOptimization::update_all();
}

int q;
int queries[155];
void read() {
    scanf("%d", &q);
    
    for (int i=0; i<q; i++) {
        scanf("%d", queries + i);
    }
}

int solve() {
    int ans[155];
    pair<int, int> pquery[155];
    
    for (int i=0; i<q; i++) {
        pquery[i].second = i;
        pquery[i].first = queries[i] - 1 >> 1;
    }

    sort(pquery, pquery + q);
    for (int i=0; i<q; i++) queries[i] = pquery[i].first, ans[i] = 0;
    
    vector<pair<int, int>> v = {{51853693,18},{82187607,16},{89920943,16},{91836893,18},{93645193,17},{109698607,17},{129291807,16},{142298343,19},{160838007,17},{162166243,26},{162252407,19},{165624493,22},{169053487,22},{173758993,16},{178165983,20},{180142893,17},{185287977,19},{189768327,18},{193724643,17},{202073607,16},{206324253,19},{211843107,19},{212963093,17},{216904033,17},{217489657,16},{218819193,16},{221956297,18},{226983307,18},{227323443,19},{232893357,18},{233083307,17},{234488357,16},{235580207,16},{238943453,19},{241845807,16},{243218877,16},{254756607,17},{263156213,17},{265943907,19},{269770743,18},{284000007,16},{286461843,16},{286992857,16},{291015057,16},{300090243,16},{303690197,16},{304479193,17},{305185577,16},{305693367,16},{306903943,22},{307885245,17},{312322593,16},{313576437,19},{317742693,23},{320095537,24},{321670757,16},{331905423,16},{336822143,17},{348347293,17},{361042443,21},{362506347,18},{363537907,17},{372742557,18},{378906757,16},{381088443,17},{385231007,18},{390011123,22},{391232197,19},{392109307,16},{394054743,16},{399207843,17},{400996497,16},{402176637,17},{403239647,16},{404986873,16},{409311027,18},{410890693,16},{411826407,25},{413293447,18},{416080127,19},{416253657,16},{417231693,17},{421446693,20},{424865407,17},{428064957,16},{430316193,16},{434859193,21},{437629457,16},{438128943,22},{446840857,17},{447066693,16},{455081827,19},{456245707,20},{460807947,16},{462227267,16},{462364557,16},{468554897,23},{471333793,17},{472470643,25},{484159333,20},{485406657,20},{486573443,17},{488050233,17},{491088907,18},{493737847,16},{494755373,23},{495170957,18},{499187307,21},{499229357,16},{501586857,17},{502897897,16},{508993343,16},{510346507,17},{522578857,18},{533998343,16},{534582183,16},{537065407,17},{538405457,16},{539290393,17},{539335493,17},{542446757,17},{542498377,20},{543545127,18},{544050307,16},{545027943,23},{545245807,17},{545347187,19},{545733443,19},{546084807,18},{557040543,19},{557244007,19},{564245443,19},{566024607,17},{571034807,18},{577313017,22},{579071693,16},{584159743,16},{585825557,19},{586306323,19},{587052887,18},{588417987,16},{590276393,16},{599832943,40},{600536193,16},{605375563,17},{605681903,18},{606573443,23},{609758193,16},{614295557,20},{614461307,20},{620466293,16},{621741557,16},{621760563,18},{622011993,16},{624161507,16},{626667943,17},{627003807,16},{628102493,16},{637366257,21},{640428443,16},{642872157,21},{646815827,18},{647386073,17},{649699357,16},{650826857,17},{654006243,16},{654997637,20},{656971957,16},{658252057,23},{659590807,18},{663237557,17},{665375693,18},{667020453,16},{667602057,16},{669025807,26},{671802383,20},{673962947,17},{674096457,19},{677430853,18},{678180443,17},{680256143,17},{683119377,17},{684412057,17},{687704243,22},{689072207,17},{691350343,17},{698186757,16},{699197117,16},{699942807,22},{701804043,19},{704010107,23},{705363443,16},{705714693,18},{706461907,16},{707665093,22},{709046213,19},{710539357,16},{711150107,18},{714012057,25},{720959507,20},{724235543,16},{725283057,20},{725338307,19},{729033453,25},{732299433,19},{735002663,19},{738890693,19},{746479193,17},{748429407,18},{750444443,16},{750548287,27},{758136943,17},{758919767,16},{760610443,17},{761087293,17},{761802293,18},{766299357,17},{766932343,16},{768062027,17},{770849373,16},{779901507,23},{781645393,20},{786168557,18},{786972113,18},{787648857,17},{787881843,16},{790926843,18},{791501797,16},{794582443,22},{796190533,17},{800465557,17},{801495893,18},{805829653,21},{805981207,18},{809881857,17},{813432443,16},{815151407,18},{817022643,16},{821140957,18},{822114457,16},{829584007,17},{830654557,20},{833673017,16},{845430347,16},{845451807,17},{850049143,22},{850995007,16},{851387893,19},{853922243,17},{854769507,16},{856611007,17},{860402083,16},{861962343,16},{863178753,16},{864535443,17},{869834857,16},{870681193,16},{878571543,18},{884836243,16},{887607557,16},{892010387,16},{895687057,21},{898030257,16},{900544523,17},{901086857,16},{904761993,17},{906601275,17},{906765257,19},{908400657,27},{911388993,16},{911832693,19},{921529357,17},{923096307,18},{923133307,16},{925068383,19},{925877753,18},{926722763,17},{928576537,19},{933743143,16},{935754243,18},{938327057,19},{938352693,17},{941304463,16},{943902887,21},{948141693,19},{948694193,17},{951786943,16},{956364943,18},{962121243,17},{965264773,17},{969677483,16},{970198343,17},{971707807,19},{977686783,17},{979846157,16},{981056523,19},{982745057,21},{983763357,16},{985821377,17},{987344883,18},{987589623,16},{989477057,16},{991122283,21},{991718957,16},{991931933,19},{992426557,19},{992637807,18},{998947357,16},{1002122857,18},{1003075507,16},{1003246457,16},{1008074207,18},{1014894343,18},{1015489093,17},{1015912503,16},{1017366917,18},{1019197443,19},{1020146357,17},{1021235717,19},{1024629943,16},{1025421457,17},{1029572773,16},{1032249057,18},{1032263253,23},{1033696607,16},{1033813737,16},{1037518807,16},{1037666557,18},{1038713723,16},{1044162243,18},{1045549627,17},{1045574447,22},{1047764193,28},{1050396953,16},{1055182643,16},{1057929843,28},{1060452193,17},{1061053557,16},{1061094257,16},{1061892203,16},{1065675443,16},{1067698757,18},{1067819007,17},{1071257257,17},{1075584037,16},{1075997307,16},{1082500113,16},{1083484277,17},{1085803893,16},{1089126943,21},{1093109337,16},{1096547213,16},{1098887093,18},{1100000143,16},{1100141693,17},{1100388627,17},{1102157893,23},{1104213157,16},{1104922603,17},{1107302633,17},{1108713807,19},{1108838307,19},{1110567453,17},{1113439943,18},{1114378023,18},{1117839407,25},{1122016537,24},{1125668757,16},{1130966377,17},{1131288881,17},{1131945693,17},{1132150703,18},{1133561993,19},{1136102677,16},{1138308657,18},{1138485057,18},{1139446407,27},{1140302587,18},{1142424093,17},{1142544343,19},{1143830537,17},{1144016203,21},{1147225633,18},{1153169207,18},{1160004193,17},{1162105277,17},{1162512577,17},{1164489043,16},{1166734943,18},{1170927857,17},{1172947443,18},{1176963393,16},{1178145743,16},{1180648423,17},{1180801393,32},{1181449693,18},{1182732793,16},{1183180123,20},{1183467943,26},{1185154443,19},{1185534657,16},{1186090157,21},{1188531807,16},{1190585297,16},{1192665443,25},{1194729957,16},{1195388137,23},{1197595443,17},{1199464193,17},{1200612603,17},{1200676287,16},{1206623607,17},{1209487937,18},{1213522887,18},{1213715693,20},{1215885743,17},{1216618307,25},{1221180563,16},{1223447207,23},{1227795057,23},{1228932843,16},{1231439893,21},{1234164443,19},{1238178557,17},{1238418163,19},{1238598057,20},{1240158743,16},{1240298207,16},{1240562757,17},{1242358707,16},{1243414557,19},{1244096537,19},{1244966793,23},{1245664243,16},{1248169057,21},{1248302193,17},{1250558457,16},{1250679243,17},{1252436193,17},{1253433787,16},{1258456607,23},{1258537493,18},{1262026667,16},{1265383257,20},{1265948507,16},{1266935743,16},{1267210953,16},{1268696957,21},{1273622943,16},{1273719777,16},{1276741357,22},{1278170343,17},{1284479357,23},{1285821737,16},{1290310663,19},{1290312057,37},{1296266603,18},{1296680793,25},{1296876157,16},{1297628067,16},{1300156307,17},{1300674807,16},{1301254807,16},{1308864557,17},{1309434407,23},{1310519007,17},{1311134843,17},{1312431557,24},{1313603273,16},{1313764977,21},{1315299193,17},{1319342107,16},{1322372927,17},{1324797093,17},{1326029193,19},{1330160057,19},{1336798923,24},{1338414943,18},{1339780443,17},{1341456787,20},{1344042393,21},{1344196243,17},{1346943307,24},{1347109457,16},{1349753943,32},{1352546057,18},{1353646497,16},{1354274043,17},{1354302743,17},{1356231183,18},{1359355993,25},{1360259607,18},{1360640403,18},{1360901693,22},{1361567557,25},{1364678957,24},{1368006307,20},{1368532693,16},{1368968507,17},{1372494443,19},{1378299697,19},{1378303607,19},{1379026693,26},{1381846653,17},{1385990893,17},{1389661307,18},{1390218643,23},{1391558277,21},{1399055923,17},{1401729503,18},{1403070193,17},{1404953597,17},{1406381257,17},{1411887693,19},{1412951307,19},{1413707807,18},{1415134443,17},{1416313193,19},{1420677943,16},{1421595807,16},{1421843743,21},{1424301943,20},{1424463893,19},{1427600557,17},{1431001507,16},{1431856457,22},{1433106243,23},{1434966307,18},{1435294143,16},{1439896557,22},{1445644143,17},{1450838407,18},{1452452643,18},{1454097393,31},{1454923057,19},{1455481737,16},{1457563047,16},{1458775963,23},{1459811943,19},{1462502057,18},{1467906357,18},{1468013057,16},{1468200193,16},{1469162521,16},{1470626093,17},{1470630003,17},{1470777053,17},{1474712077,16},{1476622597,22},{1480486093,18},{1481015193,16},{1483763013,21},{1485002147,19},{1491798443,19},{1491864057,17},{1495017557,16},{1495846477,16},{1496199593,24},{1497472553,16},{1497567557,20},};


    for (pair<int, int> p: v) {
        p.first >>= 1;
        ans[lower_bound(queries, queries + q, p.first) - queries] += p.second;
        counters[p.first >> 1] -= p.second << ((p.first & 1) << 2);
    }
    
    for (int i=1; i<q; i++) ans[i] += ans[i-1];
    
    int sum = 0;
    int lst = 0;
    for (int i=0; i<q; i++) {
        int en = queries[i] >> 1;
        for (int j=lst; j<=en; ++j) {
            sum += (counters[j] & 15) + (counters[j] >> 4 & 15);
        }
        
        lst = en + 1;
        ans[i] += sum - ((queries[i] % 2 == 0) ? counters[en] >> 4 : 0);
    }
    
    for (int i=0; i<q; i++) pquery[i].first = ans[i];
    
    sort(pquery, pquery + q, [](pair<int, int> p, pair<int, int> q) {
        return p.second < q.second;
    });
    for (int i=0; i<q; i++) printf("%d\n", pquery[i].first);
    
    return 0;
}

void test1() {
    q = 1;
    queries[0] = N;
}

void test2() {
    q = 150;
    for (int i=0; i<q; i++) queries[i] = N / (i + 1);
}

int main() {
    clock_t t = clock();
    generate_triangles();
    // read();
    test2();
    solve();
    cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}
