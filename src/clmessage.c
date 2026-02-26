static    char    sccsid[]="%Z% %M% %I% %E% %U%";
/*************************************************/
/*  Program name                                 */
/*       int       cl_get_format                 */
/* --------------------------------------------- */
/*  (I/O)                                        */
/*       Out        0   :Normal                  */
/*                 -1   :AbNormal                */
/* --------------------------------------------- */
/*  Function :                                   */
/*    言語種別に合ったメッセージのフォーマットを */
/*	  取得する									 */
/* --------------------------------------------- */
/*************************************************/
#include "colmn.h"

extern int giOptions[];
extern GlobalCt  *pGlobTable;

/********************************************/
/*                                          */
/********************************************/
char *cl_get_format(no)
int no;
{
	static tdtMessages message[]={
 {0,"Japanese","English",NULL}
,{1
,"プロセスの初期化失敗"
,"col_mn_init() error."}
,{2
,"メモスペース作成エラー ret=%d"
,"Memospace creation error ret=%d"}
,{3
,"ホストＩＤ長が不正です。"
,"invalid hostid length."}
,{4
,"自ホストＩＤ、ＤＢホストＩＤが取り出せない !!"
,"can't get myhostid and dbhostid!!"}
,{5
,"自ホストID:%s  DBホストID:%s"
,"MYHOSTID:%s  DBHOSTID:%s"}
,{6
,"自ホストＩＤ長エラー !!"
,"MYHOSTID length error!!"}
,{7
,"DBホストＩＤ長エラー !!"
,"DBHOSTID length error!!"}
,{8
,"自ホストＩＤ→ＩＰアドレス変換エラー !!"
,"MYHOSTID-->IP address convert error!!"}
,{9
,"ＤＢホストＩＤ→ＩＰアドレス変換エラー !!"
,"DBHOSTID-->IP address convert error!!"}
,{10
,"ホストID長 = %d"
,"HOSTID length = %d"}
,{11
,">> コマンド・パケットです。"
,">> Packet is command."}
,{12
,">> 現環境の初期化を行ないました。"
,">> Current environment is initialised."}
,{13
,">> コマンドを発行します。"
,">> execute command now."}
,{14
,">> R 返却パケットです。"
,">> R Packet is reply."}
,{15
,">> R 環境を戻すことができました。"
,">> R Restore environment."}
,{16
,"リターン・パケット待ちの状態でない。"
,"Status is not wait return packet."}
,{17
,">> 環境を保存しました。"
,">> store environment."}
,{21
,"*** 処理終了( %s %d.%03d sec) ret=%d"
,"*** script end( %s %d.%03d sec) ret=%d"}
,{22
,"*** 処理終了( %s %d.%03d sec) nofree no=%d ret=%d"
,"*** script end( %s %d.%03d sec) nofree no=%d ret=%d"}
,{23
,"*** clscr: メッセージ長(%d)が不正です"
,"*** clscr: Invalid message length=%d"}
,{24
,"*** clscr: メッセージの先頭が'%s'です"
,"*** clscr: Top of message is '%s'"}
,{26
,"%s: %sが閉じていません。"
,"%s: %s not closed."}
,{27
,"%s: システムエラー"
,"%s: System error"}
,{28
,"%s: リンクエラー !!"
,"%s: Link error!!"}
,{29
,"リンクエラー !!"
,"Link error!!"}
,{30
,"システムエラー"
,"System error"}
,{31
,"cllex: カッコ('(')が閉じていません(%s)。kk_level=%d"
,"cllex: parenthesis('(') not closed(%s). kk_level=%d"}
,{32
,"cllex: コメントが閉じていません(%s)。cm_level=%d"
,"cllex: comment not closed(%s). cm_level=%d"}
,{33
,"cllex: 引用符(%c)が閉じていません(%s)。"
,"cllex: quotation marks(%c) not closed(%s)."}
,{34
,"cllex: 文が終了していません(%s)。"
,"cllex: sentence not complet(%s)."}
,{35
,"cllex: [%s]は有効な文ではありません。"
,"cllex: [%s] is invalid sentence."}
,{36
,"%s: ＥＮＤＰＲＯＣまたはＥＮＤＦＵＮＣが設定されませんでした。"
,"%s: no ENDPROC or ENDFUNC."}
,{37
,"col_mn_tr_file_end: 有効な文がありません。"
,"no valid sentense."}
,{38
,"cllex: 中カッコ('{')が閉じていません(%s)。k2_level=%d"
,"cllex: brace('{') not closed(%s). k2_level=%d"}
,{39
,"cllex: 大カッコ('[')が閉じていません(%s)。k3_level=%d"
,"cllex: bracket('[') not closed(%s). k3_level=%d"}
,{40
,"cllex: スクリプトが空です。"
,"cllex: script is empty."}
,{41
,"%s: 不要なパラメータがあります。"
,"%s: There is parameter[s] of no use."}
,{42
,"%s: パラメータが足りません。"
,"%s: parameter is few."}
,{43
,"%s: 余分なパラメータ[%s]があります。"
,"%s: parameter is more [%s]."}
,{44
,"%s: パラメータが必要です。"
,"%s: parameter is required."}
,{45
,"%s: パラメータ[%s]が誤っています。"
,"%s: parameter[%s] is invalid."}
,{46
,"%s: パラメータ[%s]が数値ではありません。"
,"%s: parameter[%s] is not numeric."}
,{47
,"%s: 第 %d パラメータが誤っています(rc=%d)。"
,"%s: %d th parameter is invalid."}
,{48
,"%s: 式が誤っています(rc=%d)。"
,"%s: expression is invalid(rc=%d)."}
,{49
,""
,"%s: *** [%s] Open Error. Check up SCRIPTPATH"}
,{50
,""
,"%s: *** SCRIPTPATH=[%s]"}
,{51
,"%s: 代入式が必要です。"
,"%s: assignmaent expression is required."}
,{52
,"%s: キー[%s]中(pos=%d)に使用できない文字があります。"
,"%s: key [%s] contains an invalid character at position (pos=%d)."}
,{53
,"%s: キー[%s]が定義済みです。"
,"%s: Key [%s] is already defined."}
,{54
,"%s: ファイル名が指定されていません。"
,"%s: No file name specified."}
,{55
,"%s: if,ifdef,ifndefがないのに、[%s]が指定されました。"
,"[%s] is specified despite the absence of if,ifdef or ifndef."}
,{56
,"%s: ＬＯＯＰ/ＳＷＴＩＣＨがないのに%sが設定されました。"
,"%s: %s is set even though there is no LOOP/SWTICH."}
,{57
,"ＢＲＥＡＫ"
,"BREAK"}
,{58
,"ＣＯＮＴＩＮＵＥ"
,"CONTINUE"}
,{59
,"ラベル"
,"LABEL"}
,{61
,"%s: 先頭以外には、指定できません。"
,"%s: can't be specified inside of proc or function."}
,{66
,"ＥＮＤＬＯＯＰが有りません!!あるものとみなします。"
,"no ENDLOOP!! it shall bedeemed as present."}
,{67
,"col_mn_tr_end_node: %sがないのに%sが設定されました。"
,"col_mn_tr_end_node: without %s but %s is set."}
,{68
,"col_mn_tr_end_node: %sの後に%sは使用できません。"
,"col_mn_tr_end_node: at after %s, can't use %s."}
,{69
,"col_mn_tr_end_nodeCheck: ＥＮＤＬＯＯＰがありません。"
,"col_mn_tr_end_nodeCheck: no ENDLOOP."}
,{71
,"col_mn_tr_end_loop: ループの開始が[LOOP ]%sになっています。line=%d"
,"col_mn_tr_end_loop: start of loop is not [LOOP ]%s. line=%d"}
,{72
,"col_mn_tr_end_loop: ENDIF または ENDSW がありません。"
,"col_mn_tr_end_loop: no ENDIF or ENDSW."}
,{73
,"ＥＮＤＩＦが有りません！！あるものとみなします。"
,"no ENDIF. it shall bedeemed as present."}
,{74
,"col_mn_tr_end_loop: ループの開始がDO;またはLOOP;ではありません。line=%d"
,"col_mn_tr_end_loop: start of loop is not DO; or LOOP;. line=%d"}
,{76
,"%s: %sがありません。"
,"%s: no %s."}
,{77
,"%s: %sとの対応が取れていません。"
,"%s: unmatched with %s."}
,{78
,"%s: IFまたはLOOPまたはSWITCHがENDしていません。"
,"%s: IF or LOOP or SWITCH is not closed."}
,{79
,"%s: %sがENDしていません。"
,"%s: %s is not closed"}
,{81
,"cl_tree_main: [%s]は使用できません。"
,"cl_tree_main: [%s] is can't used."}
,{82
,"cl_tree_main: [%s]はPROC/FUNC/CLASSの外側では使用できません。"
,"cl_tree_main: [%s] is can't used outside of PROC/FUNC/CLASS."}
,{83
,"%s: パラメータが１つ必要です。"
,"%s: parameter is requied just one."}
,{84
,"cl_tree_main: [%s]はPROC/FUNC/CLASSの内側では使用できません。"
,"cl_tree_main: [%s] is can't used inside of PROC/FUNC/CLASS."}
,{86
,"col_mn_tr_exec: 手続き種別[%s]が誤っています。"
,"col_mn_tr_exec: procedure kind is invalid."}
,{91
,"col_mn_tr_if: 論理式が必要です。"
,"col_mn_tr_throw: logical expression is requied."}
,{92
,"%s: 式が必要です。"
,"%s: expression is requied."}
,{93
,"%s: 数値ではありません。"
,"%s: not numeric."}
,{94
,"col_mn_tr_leave: 転送ホストが必要です。"
,"col_mn_tr_leave: leave host name is required."}
,{96
,"%s: 右括弧')'の後ろに余分な語句[%s]があります。(sp=%d)"
,"%s: there is extra words[%s] after right parenthesis.(sp=%d)"}
,{97
,"%s: 区切り';'の位置が不正です。(sp=%d)"
,"%s: location of delimiter ';' is invalid.(sp=%d)"}
,{98
,"%s: 区切り';'が多すぎます。(sp=%d)"
,"%s: delimiter ';' is too.(sp=%d)"}
,{99
,"%s: 括弧が閉じていません。"
,"%s: parenthesis is not closed."}
,{100
,"%s: 区切り';'が足りません。"
,"%s: delimiter ';' is few."}
,{101
,"ＰＲＯＣがありません。"
,"no PROC."}
,{102
,"ＬＯＯＰがＮＥＳＴしています。"
,"loop is nested."}
,{103
,"col_mn_tr_loop: ＬＯＯＰの数または条件が必要です。"
,"col_mn_tr_loop: loop count or cndition is required."}
,{106
,"col_mn_tr_on: ＰＲＯＣの内部には、指定できません。"
,"col_mn_tr_on: [%s] can't be specified inside of PROC."}
,{107
,"col_mn_tr_on: 先頭以外には、指定できません。"
,"col_mn_tr_on: can't be specified without top."}
,{111
,"%s: %s名が必要です。"
,"%s: %s name is required."}
,{112
,"%s: %s名[%s]が長すぎます(len=%d > %d)。"
,"%s: %s name[%s] is too long(len=%d > %d)."}
,{113
,"%s: %s名[%s]が不正です。"
,"%s: %s name[%s] is invalid."}
,{114
,"手続き"
,"PROC"}
,{115
,"関数"
,"FUNCTION"}
,{116
,"%s: 値(%d)が範囲外(0-99999)です。"
,"%s: value(%d) is out of range(0-99999)."}
,{117
,"cl_rp_frm_nfrm_gen: データがバルクではありませ。"
,"cl_rp_frm_nfrm_gen: data is not bulk."}
,{118
,"フィールドの数が合わない。"
,"The number of fields does not match."}
,{119
,"スクリプト"
,"SCRIPT"}
,{120
,"クラス"
,"CLASS"}
,{121
,"%s: [%s]は予約語です。"
,"%s: [%s] is a reserved word."}
,{122
,"%s: [%s]の後の[%s]の位置が不正です。"
,"%s: After [%s],The position of [%s] is invalid."}
,{123
,"%s: 演算子がありません。%s %s"
,"%s: No operator.%s %s"}
,{124
,"%s: [%s]にアクセス修飾子は指定できません。"
,"%s: Access modifiers cannot be specified for [%s]."}
,{125
,"%s: [%s]が誤っています。"
,"%s: [%s] is incorrect."}
,{126
,"%s: %sには代入できません。"
,"%s: Cannot assign to %s."}
,{127
,"%s: %sのデータが未設定です。"
,"%s: The data for %s is not set."}
,{128
,"%s: 演算子が足りません。"
,"%s: Operator is missing."}
,{129
,"%s: [%s]index指定がありません。"
,"%s: No index specified for [%s]."}
,{130
,"配列要素値"
,"array element value"}
,{131
,"関数(%s)の戻り値"
,"Return value of function (%s)"}
,{132
,"%s: %s(%s)への代入はできません。"
,"%s: Assignment to %s(%s) is not allowed."}
,{133
,"演算結果"
,"Calculation result"}
,{134
,"範囲指定"
,"Range"}
,{135
,"%s: スコープ名[%s]が不正です。"
,"%s: Invalid scope name[%s]"}
,{136
,"%s: メンバー名[%s]が不正です。"
,"%s: Invalid menber name[%s]"}
,{137
,"%s: 配列名がないか不正です。"
,"%s: array name is missing or invalid."}
,{138
,"_ex_get_member: [%s]は、メンバー名ではありません。"
,"_ex_get_member: [%s] is not member."}
,{139
,"%s: %s名がありません。"
,"%s: no %s name."}
,{140
,"%s: %sに'%s'は指定できません。"
,"%s: in %s,You cannot specify '%s'."}
,{141
,"%s: 浮動小数点データ(%e)は、ビット演算できません。"
,"%s: Floating-point data (%e) cannot be used in bitwise operations."}
,{142
,"%s: %s(%s)は、ビット演算できません。"
,"%s: %s(%s) cannot be used in bitwise operations."}
,{143
,"%s: 文字データ(%s)は、演算できません。"
,"%s: Character data (%s) cannot be processed."}
,{144
,"%s: 数値以外は、演算できません。"
,"%s: Only numerical values can be used in calculations."}
,{145
,"%s: 二項演算式に誤りがあります。"
,"%s: There is an error in the binary expression."}
,{146
,"%s: 代入演算子(%s)が長すぎます。"
,"%s: assignment operator (%s) is too long."}
,{147
,"%s: 算術演算の第%s項に誤りがあります。"
,"%s: There is an error in the %sth term of the arithmetic operation."}
,{148
,"%s: 演算子(%s)に誤りがあります。ope kinds=%d"
,"%s: There is an error in the operator(%s). ope kinds=%d"}
,{149
,"MAPPED配列"
,"MAPPED ARRAY"}
,{150
,"配列"
,"ARRAY"}
,{151
,"変数(%s)は未定義です。"
,"Variable (%s) is undefined."}
,{152
,"データが未設定です。"
,"Data is not set."}
,{153
,"リスト"
,"LIST"}
,{154
,"構造体"
,"STRUCT"}
,{155
,"%s(%s)は指定できません。"
,"%s(%s) cannot be specified."}
,{156
,"%s定義(%s)は指定できません。"
,"The %s definition (%s) cannot be specified."}
,{157
,"%s: 項の数(%d)が２以外です。演算子=%s ope=%d"
,"%s: The number of terms (%d) is not 2. Operator = %s ope = %d"}
,{158
,"%sは指定できません。"
,"%s can't be specified."}
,{159
,"クラス・インスタンス"
,"Instance of class"}
,{160
,"%s: データ属性(%d)が指定属性(%d)と異なっています。"
,"%s: Data attribute (%d) differs from specified attribute (%d)."}
,{161
,"cl_gx_cast: %sのデータのキャストは、未サポートです。"
,"cl_gx_cast: Casting data of type %s is not supported."}
,{162
,"クラスメソッド"
,"Method of class"}
,{163
,"左辺"
,""}
,{164
,"右辺"
,""}
,{165
,"%s: 演算子=%s、この集合演算はできません。"
,""}
,{166
,"%s: [%s]メンバーは指定できません。"
,""}
,{167
,"%s: Newがありません。"
,""}
,{168
,"%s: 仮引数名[%s]が誤っています。attr=%d"
,""}
,{169
,"名前指定"
,"NAME DIRECTION"}
,{170
,"データ並び式"
,"DATA ROW"}
,{171
,"%s: SYNTAXエラー。"
,"%s: SYNTAX ERROR."}
,{172
,"%s: リテラルプール・オーバフロー。"
,"%s: Literal pool overflow."}
,{173
,"%s: オブジェクト・オーバフロー。"
,"%s: Object overflow."}
,{174
,""
,"%s: malloc error."}
,{175
,"%s: 内部エラー(アクション値が不正です)。"
,""}
,{176
,"%s: オプティマイズできませんでした。"
,"%s: Internal error (invalid action value)."}
,{177
,"%s: オプティマイズエラー。"
,"%s: Optimization error."}
,{178
,"%s: sp=%d ':'に対応する'?'がありません。"
,"%s: sp=%d There is no '?' corresponding to ':'."}
,{181
,"%s: 演算スタック・オーバフロー。"
,"%s: Operation stack overflow."}
,{182
,"%s: 内部エラー(演算子値が不正です)。"
,"%s: Internal error (operator value is invalid)."}
,{183
,"%s: データが足りません。"
,"%s: Insufficient data."}
,{184
,"%s: オブジェクトが終了していません。"
,"%s: The object has not terminated."}
,{185
,"%s: 式がありません。"
,"%s: No expression."}
,{186
,"%s: オブジェクト・データがNULLです。"
,"%s: Object data is NULL."}
,{187
,"%s: %sは、この演算は、できません。"
,"%s: %s cannot perform this operation."}
,{188
,"%s: コマンドがありません。"
,"%s: Command not found."}
,{191
,"cl_gx_func: [%s]は関数名ではありません。"
,"cl_gx_func: [%s] is not a valid function name."}
,{192
,"cl_gx_func: 関数名がありません。"
,"cl_gx_func: No such function name."}
,{196
,"cl_gx_array3: [%s]は配列名ではありません。"
,"cl_gx_array3: [%s] is not an array name."}
,{197
,"cl_gx_array3: 配列名がありません。"
,"cl_gx_array3: No array name specified."}
,{201
,"%s: インデックスが指定されていません。"
,"%s: No index specified."}
,{202
,"%s: 配列ではありません。"
,"%s: This is not an array."}
,{203
,"%s: データが未設定です。"
,"%s: Data is not set."}
,{204
,"%s: 次元数(%d)が制限値(%d)を超えています。"
,"%s: The number of dimensions (%d) exceeds the limit (%d)."}
,{205
,"%s: max_pos(%d)が制限値(%d)を超えています。調整しました。"
,"%s: max_pos(%d) exceeded the limit value (%d). Adjusted."}
,{206
,"cl_gx_range: From(%d)またはTo(%d)のデータ型は指定できません。"
,"cl_gx_range: From(%d) or data type for To(%d) cannot be specified."}
,{211
,"cl_gx_func_bexp: 関数[%s]の引数が足りません。"
,"cl_gx_func_bexp: Function [%s] is missing arguments."}
,{212
,"cl_gx_func_bexp: [%s]は関数ではありません。"
,"cl_gx_func_bexp: [%s] is not a function."}
,{213
,"cl_gx_func_bexp: [%s]は実装されていません。"
,"cl_gx_func_bexp: [%s] is not implemented."}
,{216
,""
,"_check_index: Index(%s) %s."}
,{217
,""
,"%s: ArrayInfo area malloc."}
,{218
,"%s: INDEXの型[%s]が合っていません。"
,"%s: INDEX type [%s] does not match."}
,{222
,"開始位置(%d)が不正です。"
,"The start position (%d) is invalid."}
,{223
,"個数(%d)が不正です。"
,"The number of items (%d) is invalid."}
,{224
,"データ個数(%d)が配列の個数(%d)を超えています。調整しました。"
,"The number of data items (%d) exceeds the number of elements in the array (%d). Adjusted."}
,{225
,"cl_func_list: 操作指定が不正です。"
,"cl_func_list: Invalid operation specification."}
,{226
,"cl_func_list: 操作指定(%s)が不正です。"
,"cl_func_list: Invalid operation (%s) specification."}
,{227
,"cl_func_list: リストではありません。"
,"cl_func_list: Not a list."}
,{228
,"cl_ope_list LIST_REF: 参照位置(%d)が不正です。"
,"cl_ope_list LIST_REF: Invalid reference position (%d)."}
,{229
,"%s が連想配列ではありません。"
,"%s is not an associative array."}
,{230
,"%s: 調整しました。"
,"%s: Adjusted."}
,{231
,"%s: コピー元の%s[%s]が無効です。(%d)"
,"%s: The source %s[%s] is invalid. (%d)"}
,{232
,"インデックスの初期値(%d)が不正です。"
,"The initial value of the index (%d) is invalid."}
,{233
,"指定できない配列名(%s)です。"
,"The array name (%s) cannot be specified."}
,{234
,"%s: 連想配列[%s]は、利用できません！！"
,"%s: can't use hash array[%s]!!"}
,{235
,"cl_gx_conv_index2:[%s]のインデックスサイズが0です。i=%d index=%d (def=None)"
,"cl_gx_conv_index2: Index size for [%s] is 0. i=%d index=%d (def=None)"}
,{236
,"cl_gx_conv_index2:[%s]のインデックスが範囲外です。i=%d index=%d (def=%d..%d)"
,"cl_gx_conv_index2: Index for [%s] is out of range. i=%d index=%d (def=%d..%d)"}
,{237
,"%s: 連想配列は、利用できません！！"
,"%s: can't use hash array!!"}
,{238
,"%s: 演算(%s)は使用できません。"
,"%s: The operation (%s) is not available."}
,{239
,"%s: 連想配列(%s)は指定できません。"
,"%s: An associative array (%s) cannot be specified."}
,{240
,"%s: map位置(%d)が範囲外です。(%d..%d)"
,"%s: Map position (%d) is out of bounds. (%d..%d)"}
,{241
,"%s: パラメータのデータＩＤ(id1=[%c] id2=[%c])が合っていません。"
,"%s: The parameter data IDs (id1=[%c] id2=[%c]) do not match."}
,{242
,"%s: パラメータのデータ型(attr1=%d attr2=%d)が合っていません。"
,"%s: The data types of the parameters (attr1=%d attr2=%d) do not match."}
,{243
,"%sパラメータがNULLです。"
,"%s parameter is NULL."}
,{244
,""
,"REGEX: %s"}
,{245
,"%s: 演算子(%s)に誤りがあります。"
,"The operator(%s) is incorrect."}
,{246
,"%s: 第１引数が配列ではありません。id=[%c]"
,"%s: The first argument is not an array. id=[%c]"}
,{247
,"%s: map位置(i=%d %d)が範囲外です。"
,"%s: Map position (i=%d %d) is out of range."}
,{248
,"第一"
,"1st"}
,{249
,"第二"
,"2nd"}
,{250
,"_get_pos: 範囲指定が先頭以外にあります。i=%d"
,"_get_pos: Range specification is not at the beginning. i=%d"}
,{251
,"%s: パラメータ２の型があっていません。"
,"%s: The type of parameter 2 does not match."}
,{252
,"cl_cmpt_is: パラメータ２に誤りがあります。"
,"cl_cmpt_is: Parameter 2 is incorrect."}
,{255
,""
,"CONST"}
,{256
,"cl_cmpt_agg: サポートされていない演算子(%s)です!!"
,"cl_cmpt_agg: Unsuported operater(%s)!!"}
,{261
,"zeroディバイドが発生しました。"
,"A zero divide has occurred."}
,{262
,"文字列長が負です。"
,"The string length is negative."}
,{263
,"(%d)[%s]数字がありません。"
,"(%d)[%s] No number."}
,{264
,"(%d)[%s]進数が不正です。"
,"(%d)[%s] base number is invalid."}
,{265
,"(W)(%d)[%s]オーバフローしました。"
,"(W)(%d)[%s] Overflowed."}
,{266
,"%s: パラメータの型(%04x)が数値型ではありません。"
,"%s: The parameter type (%04x) is not numeric."}
,{267
,"%s: 余分なパラメータ(nparm=%d)があります。"
,"%s: There is extra parameter (nparm=%d)."}
,{268
,"Xhash: キー長は０以上です。"
,"Xhash: The key length is 0 or greater."}
,{269
,"Xhash: 第１パラメータ[%s]が'New'ではありません。"
,"Xhash: First parameter [%s] is not 'New'."}
,{270
,"Xhash: ハッシュTableへのポインタがＮＵＬＬです。"
,"Xhash: The pointer to the hash table is NULL."}
,{271
,"Xhash: ハッシュTableが不正です。id='%c%c'"
,"Xhash: The hash table is invalid. id='%c%c'"}
,{272
,"Xhash: コマンドの指定がありません。"
,"Xhash: No command specified."}
,{273
,"Xhash: Indexの指定がありません。cmd=[%s]"
,"Xhash: No index specified. cmd=[%s]"}
,{274
,"Xhash: データは指定できません。"
,"Xhash: Data cannot be specified."}
,{275
,"Xhash: コマンドが誤っています。cmd=[%s]"
,"Xhash: Invalid command. cmd=[%s]"}
,{276
,"Xhash: 第１パラメータの型が文字型でも数値型でもありません。"
,"Xhash: The type of the first parameter is neither a character type nor a numeric type."}
,{277
,"(W)%s: (%e)オーバフローしました。"
,"(W)%s: (%e) overflowed"}
,{278
,"(W)%s: (%ld)オーバフローしました。"
,"(W)%s: (%ld) overflowed"}
,{279
,"%s: キー長(%d)＞キー定義長(%d)"
,"%s: Key length (%d) > Key definition length (%d)"}
,{280
,"(W)%s: (%s)オーバフローしました。"
,"(W)%s: (%s) overflowed"}
,{281
,"開始位置が整数ではありません。"
,"The start position is not an integer."}
,{282
,"長さが整数ではありません。"
,"The length is not an integer."}
,{284
,"replace: 置換指定が整数ではありません。"
,"replace: The replacement specification is not an integer."}
,{285
,"%s: パラメータの型(%04x)が合っていません。"
,"%s: Parameter type (%04x) does not match."}
,{286
,"parm_to_char: 変数またはデータが未定義です。"
,"parm_to_char: The variable or data is undefined."}
,{287
,"max_args(%d)が不正です。"
,"max_args(%d) is invalid."}
,{288
,"max_args(%d)が配列の個数(%d)を超えています。調整しました。"
,"max_args(%d) exceeds the number of elements in the array (%d). Adjusted."}
,{289
,"max_pos(%d)が不正です。"
,"max_pos(%d) is invalid."}
,{290
,"max_pos(%d)が配列の個数/2(%d)を超えています。調整しました。"
,"max_pos(%d) exceeds the array size/2(%d). Adjusted."}
,{291
,"%s: 変換子(%s)に誤りがあります。"
,"%s: There is an error in the conversion specifier (%s)."}
,{292
,"%s: 位取り(%d)が不正です。"
,"%s: Invalid positional notation(%d)"}
,{293
,"%s: 精度(%d)が不正です。"
,"%s: Invalid precision (%d)."}
,{294
,"(W)%s: MPA(%s) オーバフロー! set MAX value."
,"(W)%s: MPA(%s) overflow! Set MAX value."}
,{295
,"(W)%s: MPA(%s) オーバフロー!"
,"(W)%s: MPA(%s) overflow!"}
,{296
,"システムエラー(Len<0)"
,"system error (Len<0)"}
,{297
,"パラメータ"
,"parameter"}
,{298
,"%s: %s取得エラー"
,"%s: get %s error."}
,{299
,"%s[%s]に誤りがあります。"
,"There is an error in %s[%s]."}
,{300
,"%s[%s]が文字型ではありません。"
,"%s[%s] is not a character type."}
,{301
,"文字定数エラー[%s]"
,"Character constant error [%s]"}
,{302
,"定数"
,"Constant"}
,{303
,"ＡＳ形式"
,"AS format"}
,{306
,"%s: 数字以外の文字[%s]があります(pos=%d)。"
,"%s: Contains non-numeric character [%s] (pos=%d)."}
,{307
,"%s: ２進浮動小数点数[%s]の指定が誤っています(rc=%d)。"
,"%s: Invalid specification for binary floating-point number [%s] (rc=%d)."}
,{308
,"%s: １０進小数点数[%s]の指定が誤っています(rc=%d)。"
,"%s: Invalid specification for decimal floating-point number [%s] (rc=%d)."}
,{311
,"cl_gx_get_info_parm_opt: %sはパラメータに誤りがあります。"
,"cl_gx_get_info_parm_opt: %s has an invalid parameter."}
,{316
,"%s: %s(%s)のエントリ用の空きがありません。"
,"%s: No space available for entry of %s(%s)."}
,{317
,"%s: %s(%s)は未定義です。"
,"%s: %s(%s) is undefined."}
,{318
,"%s: %sは使用できません。"
,"%s: %s is not available."}
,{319
,"%s: %sは変数ではありません。"
,"%s: %s is not a variable."}
,{320
,"%s: %sのインデックス(%d)は範囲外です。"
,"Index of %s (%d) is out of range."}
,{321
,"%s: %s用のMallocエラー。"
,"%s: Malloc error for %s."}
,{322
,"%s: 変数(%s)の%sは無効です(gid=%d hash ix=%d)。"
,"%s: For variable (%s), invalid %s (gid=%d hash ix=%d)."}
,{323
,"%s: %sの%sエントリ用の空きがありません。"
,"%s: No space left for %s entries on %s."}
,{324
,"%s: SCRIPT変数[%s]は定義できません。"
,"%s: The SCRIPT variable [%s] cannot be defined."}
,{325
,"cl_gx_chk_scope:W: %sの上位にProcPathがNULLのprocがあります。"
,"cl_gx_chk_scope:W: There is a proc with ProcPath NULL above %s."}
,{326
,"手続き名"
,"Procedure Name"}
,{327
,"%s: %s名がNULLです。"
,"%s: The %s name is NULL."}
,{328
,"データリスト式"
,"DATA LIST Expression"}
,{329
,"変数"
,"variable"}
,{330
,"静的型付け配列"
,"Static-typed array"}
,{331
,"手続き(%s)が有りません。"
,"No procedure (%s) exists."}
,{332
,"SQL/SLEEP/MSG実行エラー(rc=%d)、関数の実行を終了します。"
,"SQL/SLEEP/MSG execution error (rc=%d), terminating function execution."}
,{333
,"%s: メソッド[%s]は未定義です。"
,"%s: Method [%s] is undefined."}
,{334
,"%s: 関数(%s)は使用できません。"
,"%s: The function (%s) is not available."}
,{335
,"%s: コンストラクタ[%s]は未定義です。"
,"%s: The constructor [%s] is undefined."}
,{336
,"間接ファイル[%s] Open Error"
,"Indirect File [%s] Open Error"}
,{337
,"ParmSet: パラメータ長エラー"
,"ParmSet: Parameter length error"}
,{338
,"cl_get_script_name: %sが見つかりません。"
,"cl_get_script_name: %s not found."}
,{339
,"ポインタ"
,"pointer"}
,{340
,"未設定"
,"Not set"}
,{341
,"%s: NULLパラメータは指定できません。"
,"%s: NULL parameters cannot be specified."}
,{342
,"%s: NULL値は指定できません。"
,"%s: NULL values cannot be specified."}
,{343
,"%s: オプション番号(%d)が不正です。"
,"%s: Option number (%d) is invalid."}
,{344
,"cl_proc_bexp: 演算子[%s]が'='ではありません。"
,"cl_proc_bexp: Operator [%s] is not '='."}
,{346
,"コマンドＩＤエラー !!"
,"Command ID error!!"}
,{347
,"パラメータ個数エラー !!"
,"Number of parameters error !!"}
,{348
,"パラメータからホストＩＤが取得できない !!"
,"Unable to obtain HostID from parameters!!"}
,{349
,"ホストＩＤの属性が文字でない"
,"The data type of the HostID are not characters."}
,{350
,"ホストＩＤの長さが誤っている"
,"HostID length is incorrect."}
,{351
,"ホストＩＤからＩＰアドレスが取得できない !!"
,"Unable to obtain IP address from HostID!!"}
,{352
,"すでに、LEAVEされて来ている !!"
,"LEAVE is already been done!!"}
,{356
,"該当するデータ格納エリアIDが存在しない"
,"The corresponding data storage AreaID does not exist."}
,{357
,"タプル番号の式が誤っています。ret=%d"
,"Expression for tuple number is incorrect. ret=%d"}
,{358
,"タプル番号: "
,"Tuple Number: "}
,{359
,"タプル番号が範囲外です。"
,"The tuple number is out of range."}
,{360
,"データ格納エリアID"
,"Data Storage AreaID"}
,{361
,"W: %s[%s] 長さ(%d)"
,"W: %s[%s] Length (%d)"}
,{362
,"%s[%s] 構成文字 error"
,"%s[%s] character error"}
,{365
,"%sが重複しています。"
,"%s is duplicated"}
,{366
,"前に %s があります。"
,"There is a %s ahead."}
,{367
,"カッコの対応が取れていません。"
,"The parentheses are not properly matched."}
,{371
,"フィールドの数が合わない。"
,"The number of fields does not match."}
,{372
,"%s: データ個数が0です。"
,"%s: The number of data items is 0."}
,{376
,"パラメータ数に誤りがあります。"
,"The number of parameters is incorrect."}
,{378
,"該当する項目番号が見つからない。"
,"The corresponding item number cannot be found."}
,{379
,"結合条件がない。"
,"There is no join condition."}
,{381
,"カレント・スクリプト・テーブルが見つからない"
,"Current script table not found."}
,{382
,"検索種類コードが不正です。"
,"The search type code is invalid."}
,{383
,"条件式の生成に失敗"
,"Failed to generate conditional expression"}
,{384
,"SQLの発行に失敗"
,"Failed to execute SQL"}
,{385
,"検索結果の読み込みに失敗"
,"Failed to load search results"}
,{386
,"SQLコマンド[%s]の生成に失敗"
,"Failed to generate SQL command [%s]"}
,{387
,"SQLコマンド(SELECT)の生成に失敗"
,"Failed to generate SQL command (SELECT)"}
,{388
,""
,""}
,{389
,"検索結果の受け取りに失敗しました。"
,"Failed to receive search results."}
,{391
,"iSel=%d ＩＰ以外は、実行できません。"
,"iSel=%d Only IP can be executed."}
,{392
,"cl_ex_shell: 空文です。"
,"cl_ex_shell: Empty text."}
,{393
,"cl_func_f: 引数[%s]が関数名ではありません。"
,"cl_func_f: Argument [%s] is not a valid function name."}
,{394
,"cl_func_f: 引数が不正です。"
,"cl_func_f: Invalid argument."}
,{395
,"%s: データ型(%02x)が不正です。"
,"%s: Invalid data type (%02x)."}
,{396
,"file/pipe/dir用のfpは無効です。"
,"The file/pipe/dir fp is disabled."}
,{397
,"_func_felread1: 属性(%d)が不正です。"
,"_func_felread1: Invalid attribute (%d)."}
,{398
,"%s[%s]をクローズしました。"
,"Closed %s[%s]."}
,{401
,"func_math: %s 引数を無視します。"
,"func_math: %s Argument ignored."}
,{402
,"func_math: %s 引数が負です。"
,"func_math: %s Argument is negative."}
,{403
,"func_math: %s 引数が不正です。"
,"func_math: Invalid %s argument."}
,{404
,"func_math: %s 指数値がありません。"
,"func_math: %s No exponent value."}
,{405
,"func_math: %s Ｙ座標値がありません。"
,"func_math: %s Y coordinate value is missing."}
,{406
,"cl_node_process: このコマンド[%s]は実行できません。"
,"cl_node_process: This command [%s] cannot be executed."}
,{407
,"cl_node_process: cid=%08x コマンドではありません。"
,"cl_node_process: cid=%08x is not a command."}
,{408
,"cl_node_control: ＲＥＴＵＲＮ文がありません。"
,"cl_node_control: There is no RETURN statement."}
,{411
,"%sレベル(%d)が不正です。"
,"%sLevel (%d) is invalid."}
,{412
,"%sレベル(%d)がオーバです。"
,"%sLevel (%d) is over."}
,{414
,"cl_set_logparmi: ログファイル名の型(%d)があっていません。"
,"cl_set_logparmi: The log file name type (%d) is incorrect."}
,{415
,"cl_set_logparmi: ログ番号(%d)が不正です。"
,"cl_set_logparmi: Invalid log number (%d)."}
,{416
,"外部変数[%s]が未定義です。"
,"External variable [%s] is undefined."}
,{417
,"*** 検索結果(%s)は %d 件です。"
,"*** Search results (%s) are %d items."}
,{418
,"%s: 名前付き引数の名前[%s]が誤っています。"
,"%s: The name of the named argument [%s] is incorrect."}
,{419
,"%s: 同じ名前[%s]の名前付き引数があります。"
,"%s: There is a named argument with the same name [%s]."}
,{420
,"%s: 第 %d 項目 マップインデックスに範囲指定[%s]は、指定できません。"
,"%s: Item %d: The range specification [%s] cannot be used in the map index."}
,{421
,"%s: %s:(W)%s変数[%s]が定義済みです。"
,""}
,{423
,"%s: (E)SYSTEM変数[%s]が定義済みです。"
,""}
,{424
,"%s: 手続き外ではLOCAL変数は定義できません。"
,""}
,{425
,"%s: %s変数[%s]が定義済みです。"
,""}
,{426
,"%s: %s変数[%s %s]が定義済みです。"		/* LOCAL変数[XXXX dec(10,3)]が定義済みです。 */
,""}
,{427
,"%s: 次元数(%d)が多すぎます。(>%d)"
,""}
,{428
,"%s: 第 %d 項目の範囲指定[%s]が不正です。"
,""}
,{429
,"%s: 第 %d 項目の範囲指定[%s]が数値ではありません。"
,""}
,{430
,"%s: 第 %d 項目の要素数[%s]=%dが不正です。"
,""}
,{431
,"%s: 変数名[%s]は%sではありません。"
,""}
,{432
,"%s: %s[%s]が誤っています。"
,""}
,{433
/*,"%s: システム・エラー、カッコが閉じていません。"*/
,"%s: カッコが閉じていません。"
,""}
,{434
,"cl_pr_ex_def_map_ary: 範囲指定(%d[%d,%d,%d])が変数配列の個数(%d)を超えています。"
,""}
,{435
,"%s: 変数名がありません。"
,""}
,{436
,"%s: 変数名[%s]が誤っています。"
,""}
,{437
,"%s: インデックスまたは次元の指定がありません。"
,""}
,{438
,"%s: [%s]は未定義です。"
,""}
,{439
,"%s: 定義済みMAPPEDARRAYのためインデックスまたは次元は指定できません。"
,""}
,{440
,"%s: SYNTAXが誤っています。rc=%d"
,""}
,{441
,"変数名"
,"variable name"}
,{442
,"%s: 元の属性(%d)と再定義属性(%d)が合っていません。"
,""}
,{443
,"%s: LOCALは指定できません。"
,""}
,{444
,"%s: STRUCTのメンバ[%s]は指定できません。"
,""}
,{445
,"%s: [%s]は配列ではありません。"
,""}
,{446
,"%s: %sはUNDEFINEできません。"
,""}
,{447
,"%s: HASH指定は再定義できません。"
,""}
,{448
,"%s: 範囲指定([%d,%d,%d])が配列の最大個数(%d)を超えています。"
,""}
,{449
,"%s: 定数定義が異なっています。old=%d new=%d"
,""}
,{450
,"%s: データ型が異なっています。old=%d new=%d"
,""}
,{451
,"%s: 長さが異なっています。old=%d new=%d"
,""}
,{452
,"%s: %d 次元目が異なっています。old=%d new=%d"
,""}
,{453
,"%s: システム変数名[%s]は指定できません。"
,""}
,{454
,"%s: データ型のサイズ(%d)が誤っています。"
,""}
,{455
,"%s :属性(%d)の固定長(%d)から可変長への変更(またはその逆)はでません。"
,""}
,{456
,"%s: 配列データ域(%d * %d)が最大値(%d)を超えています。"
,""}
,{457
,"%s: 型指定がありません。"
,""}
,{458
,"%s: %sは省略できません"
,""}
,{459
,"%s: %sの初期設定エラー。"
,""}
,{460
,"%s: 初期値は変数が１つのときのみ指定できます。"
,""}
,{461
,"%s: サイズ(%s)が誤っています。rc=%d"
,""}
,{462
,"%s: サイズ(%d)が誤っています。"
,""}
,{463
,"%s: 精度(%s)が誤っています。rc=%d"
,""}
,{464
,"%s: 精度(%d)が誤っています。"
,""}
,{465
,"メンバ名"
,""}
,{466
,"型定義名"
,""}
,{467
,"%s: パラメータが足りません。prmnum=%d"
,""}
,{468
,"%s: 型指定が誤っています。type=[%s]"
,""}
,{469
,"%s: \"%s\"の位置が不正です。"
,""}
,{470
,"%s: ＡＳがありません。"
,""}
,{471
,"未定義の外部関数です。"
,""}
,{472
,"%s: 構造体への初期値設定はできません。"
,""}
,{473
,"%s: 変数[%s]の配列定義ができない属性(%d)です。"
,""}
,{474
,"カンマ"
,"comma"}
,{475
,"%s: 位取り(%s)が誤っています。rc=%d"
,""}
,{476
,"%s: 位取り(%d)が誤っています。"
,""}
,{477
,"%s: 属性が誤っています。attr=[%s]"
,""}
,{478
,"%s: 長さ、または、精度、位取りの指定(%s)が誤っています。rc=%d"
,""}
,{479
,"%s: 長さ、または、精度、位取りの指定数(%d)が不正です。"
,""}
,{480
,"%s: [%s]には、長さ、または、精度、位取りは指定できません。"
,""}
,{481
,"要素用変数名"
,""}
,{482
,"%s: ＩＮがありません。"
,""}
,{483
,"%s: 対象データの式が誤っています。"
,""}
,{485
,"%s: 初期値式[%s]に'='がありません。"
,""}
,{486
,"%s: パラメータがNULLです。"
,""}
,{487
,"%s: STEPの位置が不正です。"
,""}
,{488
,"%s: STEPがありません。"
,""}
,{491
,"%s: 第一パラメータが 'GR'or '<'ではありません。"
,""}
,{496
,"%s: 変数名(%s)の長さ(%d)が長すぎます。"
,""}
,{498
,"%s: 属性指定がありません。"
,""}
,{499
,"%s: 返却値の属性指定(attr=%d size=%d precision=%d scale=%d)が不正です。"
,""}
,{500
,"%s: 仮引数名がありません。[%s]"
,""}
,{501
,"%s: %s内に文がありません。"
,""}
,{502
,"%s: %sのエントリ用の空きがありません。rc=%d"
,""}
,{503
,"%s: 仮引数が多すぎます。"
,""}
,{504
,"%s: 仮引数名(%s)の後に余分な文字(%s)があります。"
,""}
,{505
,"%s: 余分な変数(%s)があります。"
,""}
,{506
,"ＥＮＤＰＲＯＣ"
,"ENDPROC"}
,{507
,"ＥＮＤＦＵＮＣ"
,"ENDFUNC"}
,{508
,"%s: %s文に達しました。ＲＥＴＵＲＮします。"
,""}
,{509
,"%s: %d 番目に指定の仮引数名[%s]がありません。"
,""}
,{510
,"%s: 引数の設定が誤っています。ipa=%d"
,""}
,{511
,"リターン値:"
,""}
,{512
,"例外値:"
,""}
,{513
,"スコープ名"
,""}
,{514
," と "
," and "}
,{515
,"%s: 第%dパラメータ[%s]が誤っています。rc=%d"
,""}
,{516
,"ホストＩＤ"
,"HOSTID"}
,{517
,"ホスト名[%s]がdchostsにないか、アドレスを取得できません。 ret=%d"
,""}
,{518
,"タイムアウト値"
,""}
,{519
,"ＳＬＥＥＰ値"
,""}
,{520
,"cl_process_sleep_snd: ＳＬＥＥＰ値が負です。"
,""}
,{521
,"検索件数："
,""}
,{522
,"出力件数："
,""}
,{523
,"集約と項目が混在している"
,""}
,{524
,"%s: 仮引数(%s)のデフォルト値がありません。"
,""}
,{525
,"%s: 仮引数(%s)の属性の後に余分な文字(%s)があります。"
,""}
,{526
,"%s: ＡＳの位置が不正です。"
,""}
,{527
,"%s: 戻り値の属性の後に余分な文字(%s)があります。"
,""}
,{528
,"%s: 戻り値の属性は、関数以外では指定できません。"
,""}
,{529
,"%s: システム・エラー、括弧の対応が取れていません。kk_level=%d"
,""}
,{530
,"%s: 仮引数の属性指定(attr=%d size=%d precision=%d scale=%d)が不正です。"
,""}
,{531
,"%s: このデータ型(%c)は指定できません。"
,""}
,{532
,"%s: max_args(%d)が配列の個数(%d)を超えています。調整しました。"
,""}
,{533
,"%s: 項目番号指定(%d)が不正です。"
,""}
,{534
,"%s: 位置指定(%d)が不正です。"
,""}
,{535
,"%s: 長さ指定(%d)が不正です。"
,""}
,{536
,"%s: キー値が取得できません。"
,""}
,{537
,"%s: %d 件目のデータでエラー(%d)が発生しました。"
,""}
,{538
,"%s: デフォルト値(%s)が誤っています。"
,""}
,{539
,"%s: デフォルト値の後に余分な文字(%s)があります。"
,""}
,{540
,"%s: %sがありません。(%s)"
,"%s: no %s %s."}
,{541
,"%s: SWITCHとCASEの間に文があります。"
,""}
,{546
,"%s: クラス[%s]へのパスがありません"
,""}
,{547
,"%s: [%s]は、STATICではありません。sub_cid=%08x"
,""}
,{548
,"%s: クラス[%s]は未定義です。"
,""}
,{549
,"%s: [%s]にleaf情報がありません。"
,""}
,{550
,"%s: コンストラクタがメソッド[%s]を返しました。"
,""}
,{551
,""
,"%s: if syntax error!! defined only(word=[%s])."}
,{552
,""
,"%s: if syntax error!! op=[%s]"}
,{553
,""
,"%s: define word[%s] is loop!!"}
,{554
,""
,"%s: define stack over(%d)!!"}
,{555
,"_rep_def_parm: 実引数の数(%d)と仮引数の数(%d)が合っていません。"
,""}
,{556
,""
,"%s: include file[%s] is loop!!"}
,{561
,"%s: 不正なオプション[%s]です。"
,""}
,{562
,"%s: Importファイル[%s]内にmainがあります。"
,""}
,{563
,"%s: mainを無効にしました。"
,""}
,{566
,"%s: [%s]の前にＡＳが必要です。"
,""}
,{567
,"%s: 余分な文字(%s)があります。"
,""}
,{571
,"属性指定"
,"setting attribute"}
,{572
,"cl_process_get_attr: 属性指定文字エラー"
,""}
,{573
,"%s: 処理番号が誤っています。"
,""}
,{574
,"%s: 処理番号が範囲外です。"
,""}
,{575
,"%s: 外部変数[%s]が未定義です。"
,""}
,{576
,"_get_wait_time: %sの式が誤っていま。"
,""}
,{577
,"(%d)が不正です。"
,""}
,{581
,"cl_func_conv_parm: 配列名[%s]は、変数名に変換できません。"
,""}
,{582
,"ope=%d(%s) fpの属性が不正です。"
,""}
,{583
,"ope=%d(%s) fpはclose済みです。"
,""}
,{584
,"file/pipe/dir[%s]用のfpは無効です。"
,""}
,{585
,"_get_varname: [%s]は変数名に変換できません。"
,""}
,{586
,"配列データ域"
,""}
,{587
,"配列データ域構造体"
,""}
,{588
,"データ型指定"
,""}
,{589
,"未定義"
,"undefined"}
,{590
,"代入先"
,"target"}
,{591
,"%s: 取得名がNULLです。"
,""}
,{592
,"%s: 指定取得名[%s]は未サポートです。"
,""}
,{593
,"%s: オプション番号(%d)が範囲外です。"
,""}
,{594
,"(W)%s: オーバーフローが発生しました。"
,""}
,{595
,"(W)%s: アンダーフローが発生しました。"
,""}
,{596
,"%s: スーパークラス名がありません。"
,"%s: No super class name."}
,{597
,"スカラー変数または定数"
,"scalar variable or constant"}
,{598
,"ブロック"
,"block"}
,{599
,"%s: [%s]と同じ名前のブロック／ラベルがあります。line=%d"
,""}
,{601
,"変換データタイプ(%s)が誤っています。"
,""}
,{602
,"変換データタイプ(%d)が誤っています。"
,""}
,{603
,"変換エラーが %d個ありました。"
,""}
,{604
,"不可逆変換が %d個ありました。"
,""}
,{605
,"%s: 余分なパラメータ(nparm=%d [%s])があります。"
,""}
,{606
,"%s: 配列変数定義コマンドがありません。"
,""}
,{608
,"%s:(W)演算子[%s]は、指定できません。'='と見なします。"
,""}
,{609
,"cl_str2date: 日付文字列(%c)と書式(%c)が一致しないところがあります。"
,""}
,{610
,"%s: 未定義変数を含んでいます。"
,"%s: "}
,{611
,"%s:(W)変数[%s]のデータ型指定を無視しました。"
,""}
,{612
,"%s:(W)変数[%s]へのデータ代入を無視しました。"
,""}
,{613
,"%s: データＩＤ(id1=[%c] id2=[%c])が合っていません。"
,""}
,{614
,"%s: 構造体定義名が異なっています。(左辺=[%s] 右辺=[%s])"
,""}
,{615
,"%s: 構造体定義名を確認できません。"
,""}
,{616
,"%s:(W)変数[%s]の定義の違いを無視しました。"
,""}
,{617
,"%s: 変数[%s]は定義済みです。"
,""}
,{618
,"%s: 型定義情報が不正です。id=[%c] type=%d"
,""}
,{619
,"%s: 日付データは、ビット演算できません。"
,""}
,{620
,"%s: (W)リターンコード(%d)が正です。"
,""}
,{621
,"%s: %s開始位置(%d)が最大値(%d)を超えています。"
,""}
,{622
,"%s: 日付文字列[%s]が誤っています。ret=%d"
,""}
,{623
,"%s: [i][z]LIKE指定なしでLIKEパターン(%s)は指定できません。"
,""}
,{624
,"%s: 指数部が誤っています。"
,""}
,{625
,"%s: 符号が重複しています。"
,""}
,{626
,"%sで循環参照が発生しました。"
,""}
,{627
,"%s: 切り出し指定または編集指定が空です。"
,""}
,{628
,"%s: 編集指定[%s]が誤っています。"
,""}
,{629
,"%s: 編集指定が空です。"
,""}
,{630
,"%s: %s以外は指定できません。"
,"%s: It is not optional other than %s."}
,{631
,"%s: heredocの終了行[%s]がありません。"
,""}
,{632
,"%s: heredocの終端文字列[%s]が誤っています。"
,""}
,{633
,"%s: heredocの内部設定(proc->stdio[3]=%08x HereDocfp=%08x p=%08x)が不正です。"
,""}
,{634
,"%s: 虚数の位置が誤っています。"
,""}
,{635
,"複素数"
,"complex"}
,{636
,"%s: %sは指定できません。"
,"%s: %s is not optional."}
,{637
,"%s: データ種別(左辺=%s 右辺=%s)が合っていません。"
,""}
,{638
,"実数"
,"real"}
,{639
,"虚数"
,"image"}
,{640
,"%s: この環境では、%s は実行できません。"
,""}
,{641
,"%s: 実行時オプション7の0x0100をオンにして実行して下さい。実行後、Coalには復帰せずそのまま終了します。"
,""}
,{642
,"%s: 変数のアドレスを取得できませんでした。"
,"%s: can't get address of variable."}
,{643
,"定義された"
,""}
,{645
,"%s: コマンド(%s)の実行に失敗したようですが、メッセージを受け取れませんでした。"
,""}
,{646
,"%s: ループカウントが、%d に達しました。"
,""}
,{647
,"W %s: %s(%08x)の変換先コードがありません。"
,""}
,{648
,"%s: 文字コードが異なっています。項1=%d 項2=%d"
,""}
,{649
,"%s: 切り出し指定[%s]が誤っています。"
,""}
,{650
,"%s: from_code(%d)を無視します。"
,""}
,{651
,"%s: heredocの終端文字列長(%d>%d)が長すぎます。"
,""}
,{652
,"%s: データ属性(id1=[%c],%s id2=[%c])が合っていません。"
,""}
,{653
,"データ指定なしで、"
,""}
,{654
,"異なる型のデータの"
,""}
,{655
,"スカラー変数"
,"scalar variable"}
,{656
,"%s: %s"
,"%s: %s"}
,{657
,"%s: \"%s\"の位置(pos=%d)が不正です。"
,"%s: Invalid position (pos=%d) for \"%s\"."}
,{658
,"%s: (%s)の対象が、ポインタではありません。"
,""}
,{659
,"%s: コピー元%s[%s]のデータ域が再定義されたため本%sは無効です。"
,"%s: This %s is invalid because the data area of the source %s[%s] has been redefined."}
,{660
,"以降の同じメッセージを抑止します。"
,"Prevents subsequent messages of the same type."}
,{661
,"%s: ラベル(%s)がないか、GOTOできないラベルです。"
,"%s: Either the label (%s) is missing, or it is a label that cannot be GOTO."}
,{662
,"%s: ラベル書式(%s)と%s(%s)のラベル名が異なります。"
,"%s: The label format (%s) and the label name (%s) differ."}
,{663
,"%s: 仮引数(%s)(%s)には、データ型は指定できません。"
,"%s: The placeholder argument (%s)(%s) cannot have a specified data type."}
,{664
,"%s: %sの集合演算はできません。"
,"%s: Set operations are not supported for %s."}
,{665
,"%s: 指定した配列の要素数が元の配列の要素数を超えたため調整し1次元にします。"
,"%s: The number of elements in the specified array exceeded the number of elements in the original array, so it has been adjusted to one dimension."}
,{666
,"%s: 関数の再帰呼び出し回数が上限(%d)を超えました。"
,"%s: The number of recursive function calls exceeded the limit (%d)"}
,{667
,"%s: コピー先とコピー元が同じです。スキップします。"
,"%s: The destination and source are the same. Skipping."}
,{668
,"%s: データ(%s)とフォーマット(%s)が一致しません。"
,"%s: The data (%s) and format (%s) do not match."}
,{669
,"%s: 同じノード(%s %s)が実行されました。"
,"%s: The same node (%s %s) was executed."}
,{670
,"%s: 構造体定義名が異なっています。(new=[%s] old=[%s])"
,"%s: The structure definition names are different.(new=[%s] old=[%s])"}
,{671
,"%s: データＩＤが異なっています。(new=[%c] old=[%c])"
,"%s: The data IDs are different.(new=[%c] old=[%c])"}
,{672
,"文字データ"
,"character data"}
,{673
,"有理数"
,"rational number"}
,{674
,"１０進浮動小数点データ"
,"decimal data"}
,{675
,"指定位置"
,"designated location"}
,{676
,"文字型指定変数"
,"character type variable"}
,{677
,"第三"
,"3rd"}
,{678
,"システム変数"
,"system variable"}
,{679
,"子の配列"
,"child array"}
,{680
,"%s: 親の配列情報と一致しません。"
,"%s: Does not match the parent's array infomation."}
,{681
,"%s: 親の設定済み要素の最大インデックス(my=%d parent=%d)と一致しません。"
,"%s: Does not match the maximum index of the parent's predefined elements (my=%d parent=%d)."}
,{682
,"%s: [%s]または[%s]が誤っています。"
,"%s: [%s] or [%s] is incorrect."}
,{683
,"%s: %s(%s)と%s(%s)の演算はできません。"
,"%s: The operation between %s(%s) and %s(%s) is not possible."}
,{684
,"%s: %sが多すぎます。"
,"%s: Too many %s."}
,{685
,"%s: 引用符スタック(%d)がオーバフローしました。引用符=[%c]"
,"%s: Quote stack (%d) overflowed. Quote = [%c]"}
,{686
,"カッコ('(')"
,"parentheses"}
,{687
,"中カッコ('{')"
,"middle parentheses"}
,{688
,"大カッコ('[')"
,"Big Brackets"}
,{689
,"%s: %sの対応が取れていません \"%s\" rc=%d"
,"%s: unpaired %s \"%s\" rc=%d"}
,{690
,"%s: map位置(%d)が不正です。"
,"%s: Invalid map position (%d)."}
,{691
,"%s: データ個数(ida)が制限値(%d)を超えました。"
,"%s: The number of data items (ida) exceeded the limit (%d)."}
,{  -1,NULL,NULL,NULL}
};
	int kind;
	char *p;
	static tdtConvMsgHead *cmh=NULL;

	if (!cmh) cmh = akxc_conv_msg_new(message);
	kind = pGlobTable->options[13];
	if (kind < 0) kind = -kind;
	if (kind > 2) kind = 0;
	if (!(p=akxc_conv_msg(cmh,no,kind))) p = "";
	return p;
}
