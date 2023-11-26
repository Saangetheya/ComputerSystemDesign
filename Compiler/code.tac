label_30:
_t51_2 = #8
keys_0_2 = _t51_2
memory keys_2 _t51_2 #4
FunctionCall getNode
call label_1
label_31:
_t52_2 = ReturnVal
root_2 = _t52_2
_t53_2 = #0
_t54_2 = _t53_2 * #4
_t55_2 = keys_2 + _t54_2
string _t56_2 "the"
*_t55_2 = _t56_2
_t57_2 = #1
_t58_2 = _t57_2 * #4
_t59_2 = keys_2 + _t58_2
string _t60_2 "a"
*_t59_2 = _t60_2
_t61_2 = #2
_t62_2 = _t61_2 * #4
_t63_2 = keys_2 + _t62_2
string _t64_2 "there"
*_t63_2 = _t64_2
_t65_2 = #3
_t66_2 = _t65_2 * #4
_t67_2 = keys_2 + _t66_2
string _t68_2 "answer"
*_t67_2 = _t68_2
_t69_2 = #4
_t70_2 = _t69_2 * #4
_t71_2 = keys_2 + _t70_2
string _t72_2 "any"
*_t71_2 = _t72_2
_t73_2 = #5
_t74_2 = _t73_2 * #4
_t75_2 = keys_2 + _t74_2
string _t76_2 "by"
*_t75_2 = _t76_2
_t77_2 = #6
_t78_2 = _t77_2 * #4
_t79_2 = keys_2 + _t78_2
string _t80_2 "bye"
*_t79_2 = _t80_2
_t81_2 = #7
_t82_2 = _t81_2 * #4
_t83_2 = keys_2 + _t82_2
string _t84_2 "their"
*_t83_2 = _t84_2
_t85_2 = #0
_t86_2 = _t85_2 * #4
_t87_2 = keys_2 + _t86_2
first_2 = *_t87_2
_t88_2 = #32765
_t89_2 = #32765
_t90_2 = _t88_2 / _t89_2
n_2 = _t90_2
_t91_3 = #0
i_2 = _t91_3
label_32:
_t92_3 = i_2 < n_2
if ( _t92_3 == #0 ) goto label_35
goto label_33
label_34:
_t93_3 = i_2
i_2 = i_2 + #1
goto label_32
label_33:
FunctionCall insert
param root_2
_t94_3 = i_2 * #4
_t95_3 = keys_2 + _t94_3
param *_t95_3
call label_13
label_36:
_t96_3 = ReturnVal
goto label_34
label_35:
FunctionCall search
param root_2
string _t97_2 "the"
param _t97_2
call label_22
label_37:
_t98_2 = ReturnVal
is_present_2 = _t98_2
_t99_2 = #0
Return _t99_2

label_1:
_t1_2 = #108
memory _t2_2 _t1_2 #1
pNode_2 = _t2_2
_t3_2 = #0
*pNode.isEndOfWord_2 = _t3_2
_t4_3 = #0
i_2 = _t4_3
label_2:
_t5_3 = i_2 < ALPHABET_SIZE_0
if ( _t5_3 == #0 ) goto label_5
goto label_3
label_4:
_t6_3 = i_2
i_2 = i_2 + #1
goto label_2
label_3:
_t7_3 = i_2 * #4
_t8_3 = *pNode.children_2 + _t7_3
_t9_3 = #0
*_t8_3 = _t9_3
goto label_4
label_5:
Return pNode_2

label_6:
_t10_2 = #0
count_2 = _t10_2
label_7:
_t11_3 = #1
if ( _t11_3 == #0 ) goto label_10
goto label_8
label_9:
goto label_7
label_8:
_t12_3 = count_2 * #1
_t13_3 = str_2 + _t12_3
ch_3 = *_t13_3
_t14_3 = #0
_t15_3 = ch_3 == _t14_3
if ( _t15_3 == #0 ) goto label_11
goto label_10
goto label_12
label_11:
label_12:
_t16_3 = count_2
count_2 = count_2 + #1
goto label_9
label_10:
Return count_2

label_13:
pCrawl_2 = root_2
FunctionCall strlen
param key_2
call label_6
label_14:
_t17_2 = ReturnVal
n_2 = _t17_2
_t18_3 = #0
i_2 = _t18_3
label_15:
_t19_3 = i_2 < n_2
if ( _t19_3 == #0 ) goto label_18
goto label_16
label_17:
_t20_3 = i_2
i_2 = i_2 + #1
goto label_15
label_16:
_t21_3 = i_2 * #1
_t22_3 = key_2 + _t21_3
_t23_3 = #'a'
_t24_3 = *_t22_3 - _t23_3
index_3 = _t24_3
_t25_3 = index_3 * #4
_t26_3 = *pCrawl.children_2 + _t25_3
_t27_3 = #0
_t28_3 = *_t26_3 != _t27_3
if ( _t28_3 == #0 ) goto label_19
_t29_4 = index_3 * #4
_t30_4 = *pCrawl.children_2 + _t29_4
FunctionCall getNode
call label_1
label_21:
_t31_4 = ReturnVal
*_t30_4 = _t31_4
goto label_20
label_19:
label_20:
_t32_3 = index_3 * #4
_t33_3 = *pCrawl.children_2 + _t32_3
pCrawl_2 = *_t33_3
goto label_17
label_18:
_t34_2 = #1
*pCrawl.isEndOfWord_2 = _t34_2
_t35_2 = #1
Return _t35_2

label_22:
pCrawl_2 = root_2
FunctionCall strlen
param key_2
call label_6
label_23:
_t36_2 = ReturnVal
n_2 = _t36_2
_t37_3 = #0
i_2 = _t37_3
label_24:
_t38_3 = i_2 < n_2
if ( _t38_3 == #0 ) goto label_27
goto label_25
label_26:
_t39_3 = i_2
i_2 = i_2 + #1
goto label_24
label_25:
_t40_3 = i_2 * #1
_t41_3 = key_2 + _t40_3
_t42_3 = #'a'
_t43_3 = *_t41_3 - _t42_3
index_3 = _t43_3
_t44_3 = index_3 * #4
_t45_3 = *pCrawl.children_2 + _t44_3
_t46_3 = #0
_t47_3 = *_t45_3 != _t46_3
if ( _t47_3 == #0 ) goto label_28
_t48_4 = #0
Return _t48_4
goto label_29
label_28:
label_29:
_t49_3 = index_3 * #4
_t50_3 = *pCrawl.children_2 + _t49_3
pCrawl_2 = *_t50_3
goto label_26
label_27:
Return *pCrawl.isEndOfWord_2

