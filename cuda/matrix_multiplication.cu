



<!DOCTYPE html>
<html>
<head>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" >
 
 <meta name="ROBOTS" content="NOARCHIVE">
 
 <link rel="icon" type="image/vnd.microsoft.icon" href="https://ssl.gstatic.com/codesite/ph/images/phosting.ico">
 
 
 <script type="text/javascript">
 
 
 
 
 var codesite_token = "xgsVxMDtRHqTM3kVI14V3MX5LPc:1371808347652";
 
 
 var CS_env = {"assetVersionPath":"https://ssl.gstatic.com/codesite/ph/18376132045800511552","token":"xgsVxMDtRHqTM3kVI14V3MX5LPc:1371808347652","projectHomeUrl":"/p/stanford-cs193g-sp2010","projectName":"stanford-cs193g-sp2010","loggedInUserEmail":"gaurav.sachin007@gmail.com","relativeBaseUrl":"","assetHostPath":"https://ssl.gstatic.com/codesite/ph","domainName":null,"profileUrl":"/u/116699586124044253698/"};
 var _gaq = _gaq || [];
 _gaq.push(
 ['siteTracker._setAccount', 'UA-18071-1'],
 ['siteTracker._trackPageview']);
 
 (function() {
 var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
 ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
 (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(ga);
 })();
 
 </script>
 
 
 <title>matrix_multiplication.cu - 
 stanford-cs193g-sp2010 -
 
 
 Programming Massively Parallel Processors with CUDA - Google Project Hosting
 </title>
 <link type="text/css" rel="stylesheet" href="https://ssl.gstatic.com/codesite/ph/18376132045800511552/css/core.css">
 
 <link type="text/css" rel="stylesheet" href="https://ssl.gstatic.com/codesite/ph/18376132045800511552/css/ph_detail.css" >
 
 
 <link type="text/css" rel="stylesheet" href="https://ssl.gstatic.com/codesite/ph/18376132045800511552/css/d_sb.css" >
 
 
 
<!--[if IE]>
 <link type="text/css" rel="stylesheet" href="https://ssl.gstatic.com/codesite/ph/18376132045800511552/css/d_ie.css" >
<![endif]-->
 <style type="text/css">
 .menuIcon.off { background: no-repeat url(https://ssl.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -42px }
 .menuIcon.on { background: no-repeat url(https://ssl.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -28px }
 .menuIcon.down { background: no-repeat url(https://ssl.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 0; }
 
 
 
  tr.inline_comment {
 background: #fff;
 vertical-align: top;
 }
 div.draft, div.published {
 padding: .3em;
 border: 1px solid #999; 
 margin-bottom: .1em;
 font-family: arial, sans-serif;
 max-width: 60em;
 }
 div.draft {
 background: #ffa;
 } 
 div.published {
 background: #e5ecf9;
 }
 div.published .body, div.draft .body {
 padding: .5em .1em .1em .1em;
 max-width: 60em;
 white-space: pre-wrap;
 white-space: -moz-pre-wrap;
 white-space: -pre-wrap;
 white-space: -o-pre-wrap;
 word-wrap: break-word;
 font-size: 1em;
 }
 div.draft .actions {
 margin-left: 1em;
 font-size: 90%;
 }
 div.draft form {
 padding: .5em .5em .5em 0;
 }
 div.draft textarea, div.published textarea {
 width: 95%;
 height: 10em;
 font-family: arial, sans-serif;
 margin-bottom: .5em;
 }

 
 .nocursor, .nocursor td, .cursor_hidden, .cursor_hidden td {
 background-color: white;
 height: 2px;
 }
 .cursor, .cursor td {
 background-color: darkblue;
 height: 2px;
 display: '';
 }
 
 
.list {
 border: 1px solid white;
 border-bottom: 0;
}

 
 </style>
</head>
<body class="t4">
<script type="text/javascript">
 window.___gcfg = {lang: 'en'};
 (function() 
 {var po = document.createElement("script");
 po.type = "text/javascript"; po.async = true;po.src = "https://apis.google.com/js/plusone.js";
 var s = document.getElementsByTagName("script")[0];
 s.parentNode.insertBefore(po, s);
 })();
</script>
<div class="headbg">

 <div id="gaia">
 

 <span>
 
 
 
 <a href="#" id="multilogin-dropdown" onclick="return false;"
 ><u><b>gaurav.sachin007@gmail.com</b></u> <small>&#9660;</small></a>
 
 
 | <a href="/u/116699586124044253698/" id="projects-dropdown" onclick="return false;"
 ><u>My favorites</u> <small>&#9660;</small></a>
 | <a href="/u/116699586124044253698/" onclick="_CS_click('/gb/ph/profile');"
 title="Profile, Updates, and Settings"
 ><u>Profile</u></a>
 | <a href="https://www.google.com/accounts/Logout?continue=https%3A%2F%2Fcode.google.com%2Fp%2Fstanford-cs193g-sp2010%2Fsource%2Fbrowse%2Ftrunk%2Ftutorials%2Fmatrix_multiplication.cu" 
 onclick="_CS_click('/gb/ph/signout');"
 ><u>Sign out</u></a>
 
 </span>

 </div>

 <div class="gbh" style="left: 0pt;"></div>
 <div class="gbh" style="right: 0pt;"></div>
 
 
 <div style="height: 1px"></div>
<!--[if lte IE 7]>
<div style="text-align:center;">
Your version of Internet Explorer is not supported. Try a browser that
contributes to open source, such as <a href="http://www.firefox.com">Firefox</a>,
<a href="http://www.google.com/chrome">Google Chrome</a>, or
<a href="http://code.google.com/chrome/chromeframe/">Google Chrome Frame</a>.
</div>
<![endif]-->



 <table style="padding:0px; margin: 0px 0px 10px 0px; width:100%" cellpadding="0" cellspacing="0"
 itemscope itemtype="http://schema.org/CreativeWork">
 <tr style="height: 58px;">
 
 
 
 <td id="plogo">
 <link itemprop="url" href="/p/stanford-cs193g-sp2010">
 <a href="/p/stanford-cs193g-sp2010/">
 
 <img src="https://ssl.gstatic.com/codesite/ph/images/defaultlogo.png" alt="Logo" itemprop="image">
 
 </a>
 </td>
 
 <td style="padding-left: 0.5em">
 
 <div id="pname">
 <a href="/p/stanford-cs193g-sp2010/"><span itemprop="name">stanford-cs193g-sp2010</span></a>
 </div>
 
 <div id="psum">
 <a id="project_summary_link"
 href="/p/stanford-cs193g-sp2010/"><span itemprop="description">Programming Massively Parallel Processors with CUDA</span></a>
 
 </div>
 
 
 </td>
 <td style="white-space:nowrap;text-align:right; vertical-align:bottom;">
 
 <form action="/hosting/search">
 <input size="30" name="q" value="" type="text">
 
 <input type="submit" name="projectsearch" value="Search projects" >
 </form>
 
 </tr>
 </table>

</div>

 
<div id="mt" class="gtb"> 
 <a href="/p/stanford-cs193g-sp2010/" class="tab ">Project&nbsp;Home</a>
 
 
 
 
 
 
 <a href="/p/stanford-cs193g-sp2010/w/list" class="tab ">Wiki</a>
 
 
 
 
 
 <a href="/p/stanford-cs193g-sp2010/issues/list"
 class="tab ">Issues</a>
 
 
 
 
 
 <a href="/p/stanford-cs193g-sp2010/source/checkout"
 class="tab active">Source</a>
 
 
 
 
 
 
 
 
 <div class=gtbc></div>
</div>
<table cellspacing="0" cellpadding="0" width="100%" align="center" border="0" class="st">
 <tr>
 
 
 
 
 
 
 <td class="subt">
 <div class="st2">
 <div class="isf">
 
 


 <span class="inst1"><a href="/p/stanford-cs193g-sp2010/source/checkout">Checkout</a></span> &nbsp;
 <span class="inst2"><a href="/p/stanford-cs193g-sp2010/source/browse/">Browse</a></span> &nbsp;
 <span class="inst3"><a href="/p/stanford-cs193g-sp2010/source/list">Changes</a></span> &nbsp;
 
 
 
 
 
 
 
 </form>
 <script type="text/javascript">
 
 function codesearchQuery(form) {
 var query = document.getElementById('q').value;
 if (query) { form.action += '%20' + query; }
 }
 </script>
 </div>
</div>

 </td>
 
 
 
 <td align="right" valign="top" class="bevel-right"></td>
 </tr>
</table>


<script type="text/javascript">
 var cancelBubble = false;
 function _go(url) { document.location = url; }
</script>
<div id="maincol"
 
>

 




<div class="expand">
<div id="colcontrol">
<style type="text/css">
 #file_flipper { white-space: nowrap; padding-right: 2em; }
 #file_flipper.hidden { display: none; }
 #file_flipper .pagelink { color: #0000CC; text-decoration: underline; }
 #file_flipper #visiblefiles { padding-left: 0.5em; padding-right: 0.5em; }
</style>
<table id="nav_and_rev" class="list"
 cellpadding="0" cellspacing="0" width="100%">
 <tr>
 
 <td nowrap="nowrap" class="src_crumbs src_nav" width="33%">
 <strong class="src_nav">Source path:&nbsp;</strong>
 <span id="crumb_root">
 
 <a href="/p/stanford-cs193g-sp2010/source/browse/">svn</a>/&nbsp;</span>
 <span id="crumb_links" class="ifClosed"><a href="/p/stanford-cs193g-sp2010/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span><a href="/p/stanford-cs193g-sp2010/source/browse/trunk/tutorials/">tutorials</a><span class="sp">/&nbsp;</span>matrix_multiplication.cu</span>
 
 


 </td>
 
 
 <td nowrap="nowrap" width="33%" align="center">
 <a href="/p/stanford-cs193g-sp2010/source/browse/trunk/tutorials/matrix_multiplication.cu?edit=1"
 ><img src="https://ssl.gstatic.com/codesite/ph/images/pencil-y14.png"
 class="edit_icon">Edit file</a>
 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper"><b>r285</b></td>
 
 </tr></table>
 </td> 
 </tr>
</table>

<div class="fc">
 
 
 
<style type="text/css">
.undermouse span {
 background-image: url(https://ssl.gstatic.com/codesite/ph/images/comments.gif); }
</style>
<table class="opened" id="review_comment_area"
><tr>
<td id="nums">
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
<pre><table width="100%" id="nums_table_0"><tr id="gr_svn285_1"

><td id="1"><a href="#1">1</a></td></tr
><tr id="gr_svn285_2"

><td id="2"><a href="#2">2</a></td></tr
><tr id="gr_svn285_3"

><td id="3"><a href="#3">3</a></td></tr
><tr id="gr_svn285_4"

><td id="4"><a href="#4">4</a></td></tr
><tr id="gr_svn285_5"

><td id="5"><a href="#5">5</a></td></tr
><tr id="gr_svn285_6"

><td id="6"><a href="#6">6</a></td></tr
><tr id="gr_svn285_7"

><td id="7"><a href="#7">7</a></td></tr
><tr id="gr_svn285_8"

><td id="8"><a href="#8">8</a></td></tr
><tr id="gr_svn285_9"

><td id="9"><a href="#9">9</a></td></tr
><tr id="gr_svn285_10"

><td id="10"><a href="#10">10</a></td></tr
><tr id="gr_svn285_11"

><td id="11"><a href="#11">11</a></td></tr
><tr id="gr_svn285_12"

><td id="12"><a href="#12">12</a></td></tr
><tr id="gr_svn285_13"

><td id="13"><a href="#13">13</a></td></tr
><tr id="gr_svn285_14"

><td id="14"><a href="#14">14</a></td></tr
><tr id="gr_svn285_15"

><td id="15"><a href="#15">15</a></td></tr
><tr id="gr_svn285_16"

><td id="16"><a href="#16">16</a></td></tr
><tr id="gr_svn285_17"

><td id="17"><a href="#17">17</a></td></tr
><tr id="gr_svn285_18"

><td id="18"><a href="#18">18</a></td></tr
><tr id="gr_svn285_19"

><td id="19"><a href="#19">19</a></td></tr
><tr id="gr_svn285_20"

><td id="20"><a href="#20">20</a></td></tr
><tr id="gr_svn285_21"

><td id="21"><a href="#21">21</a></td></tr
><tr id="gr_svn285_22"

><td id="22"><a href="#22">22</a></td></tr
><tr id="gr_svn285_23"

><td id="23"><a href="#23">23</a></td></tr
><tr id="gr_svn285_24"

><td id="24"><a href="#24">24</a></td></tr
><tr id="gr_svn285_25"

><td id="25"><a href="#25">25</a></td></tr
><tr id="gr_svn285_26"

><td id="26"><a href="#26">26</a></td></tr
><tr id="gr_svn285_27"

><td id="27"><a href="#27">27</a></td></tr
><tr id="gr_svn285_28"

><td id="28"><a href="#28">28</a></td></tr
><tr id="gr_svn285_29"

><td id="29"><a href="#29">29</a></td></tr
><tr id="gr_svn285_30"

><td id="30"><a href="#30">30</a></td></tr
><tr id="gr_svn285_31"

><td id="31"><a href="#31">31</a></td></tr
><tr id="gr_svn285_32"

><td id="32"><a href="#32">32</a></td></tr
><tr id="gr_svn285_33"

><td id="33"><a href="#33">33</a></td></tr
><tr id="gr_svn285_34"

><td id="34"><a href="#34">34</a></td></tr
><tr id="gr_svn285_35"

><td id="35"><a href="#35">35</a></td></tr
><tr id="gr_svn285_36"

><td id="36"><a href="#36">36</a></td></tr
><tr id="gr_svn285_37"

><td id="37"><a href="#37">37</a></td></tr
><tr id="gr_svn285_38"

><td id="38"><a href="#38">38</a></td></tr
><tr id="gr_svn285_39"

><td id="39"><a href="#39">39</a></td></tr
><tr id="gr_svn285_40"

><td id="40"><a href="#40">40</a></td></tr
><tr id="gr_svn285_41"

><td id="41"><a href="#41">41</a></td></tr
><tr id="gr_svn285_42"

><td id="42"><a href="#42">42</a></td></tr
><tr id="gr_svn285_43"

><td id="43"><a href="#43">43</a></td></tr
><tr id="gr_svn285_44"

><td id="44"><a href="#44">44</a></td></tr
><tr id="gr_svn285_45"

><td id="45"><a href="#45">45</a></td></tr
><tr id="gr_svn285_46"

><td id="46"><a href="#46">46</a></td></tr
><tr id="gr_svn285_47"

><td id="47"><a href="#47">47</a></td></tr
><tr id="gr_svn285_48"

><td id="48"><a href="#48">48</a></td></tr
><tr id="gr_svn285_49"

><td id="49"><a href="#49">49</a></td></tr
><tr id="gr_svn285_50"

><td id="50"><a href="#50">50</a></td></tr
><tr id="gr_svn285_51"

><td id="51"><a href="#51">51</a></td></tr
><tr id="gr_svn285_52"

><td id="52"><a href="#52">52</a></td></tr
><tr id="gr_svn285_53"

><td id="53"><a href="#53">53</a></td></tr
><tr id="gr_svn285_54"

><td id="54"><a href="#54">54</a></td></tr
><tr id="gr_svn285_55"

><td id="55"><a href="#55">55</a></td></tr
><tr id="gr_svn285_56"

><td id="56"><a href="#56">56</a></td></tr
><tr id="gr_svn285_57"

><td id="57"><a href="#57">57</a></td></tr
><tr id="gr_svn285_58"

><td id="58"><a href="#58">58</a></td></tr
><tr id="gr_svn285_59"

><td id="59"><a href="#59">59</a></td></tr
><tr id="gr_svn285_60"

><td id="60"><a href="#60">60</a></td></tr
><tr id="gr_svn285_61"

><td id="61"><a href="#61">61</a></td></tr
><tr id="gr_svn285_62"

><td id="62"><a href="#62">62</a></td></tr
><tr id="gr_svn285_63"

><td id="63"><a href="#63">63</a></td></tr
><tr id="gr_svn285_64"

><td id="64"><a href="#64">64</a></td></tr
><tr id="gr_svn285_65"

><td id="65"><a href="#65">65</a></td></tr
><tr id="gr_svn285_66"

><td id="66"><a href="#66">66</a></td></tr
><tr id="gr_svn285_67"

><td id="67"><a href="#67">67</a></td></tr
><tr id="gr_svn285_68"

><td id="68"><a href="#68">68</a></td></tr
><tr id="gr_svn285_69"

><td id="69"><a href="#69">69</a></td></tr
><tr id="gr_svn285_70"

><td id="70"><a href="#70">70</a></td></tr
><tr id="gr_svn285_71"

><td id="71"><a href="#71">71</a></td></tr
><tr id="gr_svn285_72"

><td id="72"><a href="#72">72</a></td></tr
><tr id="gr_svn285_73"

><td id="73"><a href="#73">73</a></td></tr
><tr id="gr_svn285_74"

><td id="74"><a href="#74">74</a></td></tr
><tr id="gr_svn285_75"

><td id="75"><a href="#75">75</a></td></tr
><tr id="gr_svn285_76"

><td id="76"><a href="#76">76</a></td></tr
><tr id="gr_svn285_77"

><td id="77"><a href="#77">77</a></td></tr
><tr id="gr_svn285_78"

><td id="78"><a href="#78">78</a></td></tr
><tr id="gr_svn285_79"

><td id="79"><a href="#79">79</a></td></tr
><tr id="gr_svn285_80"

><td id="80"><a href="#80">80</a></td></tr
><tr id="gr_svn285_81"

><td id="81"><a href="#81">81</a></td></tr
><tr id="gr_svn285_82"

><td id="82"><a href="#82">82</a></td></tr
><tr id="gr_svn285_83"

><td id="83"><a href="#83">83</a></td></tr
><tr id="gr_svn285_84"

><td id="84"><a href="#84">84</a></td></tr
><tr id="gr_svn285_85"

><td id="85"><a href="#85">85</a></td></tr
><tr id="gr_svn285_86"

><td id="86"><a href="#86">86</a></td></tr
><tr id="gr_svn285_87"

><td id="87"><a href="#87">87</a></td></tr
><tr id="gr_svn285_88"

><td id="88"><a href="#88">88</a></td></tr
><tr id="gr_svn285_89"

><td id="89"><a href="#89">89</a></td></tr
><tr id="gr_svn285_90"

><td id="90"><a href="#90">90</a></td></tr
><tr id="gr_svn285_91"

><td id="91"><a href="#91">91</a></td></tr
><tr id="gr_svn285_92"

><td id="92"><a href="#92">92</a></td></tr
><tr id="gr_svn285_93"

><td id="93"><a href="#93">93</a></td></tr
><tr id="gr_svn285_94"

><td id="94"><a href="#94">94</a></td></tr
><tr id="gr_svn285_95"

><td id="95"><a href="#95">95</a></td></tr
><tr id="gr_svn285_96"

><td id="96"><a href="#96">96</a></td></tr
><tr id="gr_svn285_97"

><td id="97"><a href="#97">97</a></td></tr
><tr id="gr_svn285_98"

><td id="98"><a href="#98">98</a></td></tr
><tr id="gr_svn285_99"

><td id="99"><a href="#99">99</a></td></tr
><tr id="gr_svn285_100"

><td id="100"><a href="#100">100</a></td></tr
><tr id="gr_svn285_101"

><td id="101"><a href="#101">101</a></td></tr
><tr id="gr_svn285_102"

><td id="102"><a href="#102">102</a></td></tr
><tr id="gr_svn285_103"

><td id="103"><a href="#103">103</a></td></tr
><tr id="gr_svn285_104"

><td id="104"><a href="#104">104</a></td></tr
><tr id="gr_svn285_105"

><td id="105"><a href="#105">105</a></td></tr
><tr id="gr_svn285_106"

><td id="106"><a href="#106">106</a></td></tr
><tr id="gr_svn285_107"

><td id="107"><a href="#107">107</a></td></tr
><tr id="gr_svn285_108"

><td id="108"><a href="#108">108</a></td></tr
><tr id="gr_svn285_109"

><td id="109"><a href="#109">109</a></td></tr
><tr id="gr_svn285_110"

><td id="110"><a href="#110">110</a></td></tr
><tr id="gr_svn285_111"

><td id="111"><a href="#111">111</a></td></tr
><tr id="gr_svn285_112"

><td id="112"><a href="#112">112</a></td></tr
><tr id="gr_svn285_113"

><td id="113"><a href="#113">113</a></td></tr
><tr id="gr_svn285_114"

><td id="114"><a href="#114">114</a></td></tr
><tr id="gr_svn285_115"

><td id="115"><a href="#115">115</a></td></tr
><tr id="gr_svn285_116"

><td id="116"><a href="#116">116</a></td></tr
><tr id="gr_svn285_117"

><td id="117"><a href="#117">117</a></td></tr
><tr id="gr_svn285_118"

><td id="118"><a href="#118">118</a></td></tr
><tr id="gr_svn285_119"

><td id="119"><a href="#119">119</a></td></tr
><tr id="gr_svn285_120"

><td id="120"><a href="#120">120</a></td></tr
><tr id="gr_svn285_121"

><td id="121"><a href="#121">121</a></td></tr
><tr id="gr_svn285_122"

><td id="122"><a href="#122">122</a></td></tr
><tr id="gr_svn285_123"

><td id="123"><a href="#123">123</a></td></tr
><tr id="gr_svn285_124"

><td id="124"><a href="#124">124</a></td></tr
><tr id="gr_svn285_125"

><td id="125"><a href="#125">125</a></td></tr
><tr id="gr_svn285_126"

><td id="126"><a href="#126">126</a></td></tr
><tr id="gr_svn285_127"

><td id="127"><a href="#127">127</a></td></tr
><tr id="gr_svn285_128"

><td id="128"><a href="#128">128</a></td></tr
><tr id="gr_svn285_129"

><td id="129"><a href="#129">129</a></td></tr
><tr id="gr_svn285_130"

><td id="130"><a href="#130">130</a></td></tr
><tr id="gr_svn285_131"

><td id="131"><a href="#131">131</a></td></tr
><tr id="gr_svn285_132"

><td id="132"><a href="#132">132</a></td></tr
><tr id="gr_svn285_133"

><td id="133"><a href="#133">133</a></td></tr
><tr id="gr_svn285_134"

><td id="134"><a href="#134">134</a></td></tr
><tr id="gr_svn285_135"

><td id="135"><a href="#135">135</a></td></tr
><tr id="gr_svn285_136"

><td id="136"><a href="#136">136</a></td></tr
><tr id="gr_svn285_137"

><td id="137"><a href="#137">137</a></td></tr
><tr id="gr_svn285_138"

><td id="138"><a href="#138">138</a></td></tr
><tr id="gr_svn285_139"

><td id="139"><a href="#139">139</a></td></tr
><tr id="gr_svn285_140"

><td id="140"><a href="#140">140</a></td></tr
><tr id="gr_svn285_141"

><td id="141"><a href="#141">141</a></td></tr
><tr id="gr_svn285_142"

><td id="142"><a href="#142">142</a></td></tr
><tr id="gr_svn285_143"

><td id="143"><a href="#143">143</a></td></tr
><tr id="gr_svn285_144"

><td id="144"><a href="#144">144</a></td></tr
><tr id="gr_svn285_145"

><td id="145"><a href="#145">145</a></td></tr
><tr id="gr_svn285_146"

><td id="146"><a href="#146">146</a></td></tr
><tr id="gr_svn285_147"

><td id="147"><a href="#147">147</a></td></tr
><tr id="gr_svn285_148"

><td id="148"><a href="#148">148</a></td></tr
><tr id="gr_svn285_149"

><td id="149"><a href="#149">149</a></td></tr
><tr id="gr_svn285_150"

><td id="150"><a href="#150">150</a></td></tr
><tr id="gr_svn285_151"

><td id="151"><a href="#151">151</a></td></tr
><tr id="gr_svn285_152"

><td id="152"><a href="#152">152</a></td></tr
><tr id="gr_svn285_153"

><td id="153"><a href="#153">153</a></td></tr
><tr id="gr_svn285_154"

><td id="154"><a href="#154">154</a></td></tr
><tr id="gr_svn285_155"

><td id="155"><a href="#155">155</a></td></tr
><tr id="gr_svn285_156"

><td id="156"><a href="#156">156</a></td></tr
><tr id="gr_svn285_157"

><td id="157"><a href="#157">157</a></td></tr
><tr id="gr_svn285_158"

><td id="158"><a href="#158">158</a></td></tr
><tr id="gr_svn285_159"

><td id="159"><a href="#159">159</a></td></tr
><tr id="gr_svn285_160"

><td id="160"><a href="#160">160</a></td></tr
><tr id="gr_svn285_161"

><td id="161"><a href="#161">161</a></td></tr
><tr id="gr_svn285_162"

><td id="162"><a href="#162">162</a></td></tr
><tr id="gr_svn285_163"

><td id="163"><a href="#163">163</a></td></tr
><tr id="gr_svn285_164"

><td id="164"><a href="#164">164</a></td></tr
><tr id="gr_svn285_165"

><td id="165"><a href="#165">165</a></td></tr
><tr id="gr_svn285_166"

><td id="166"><a href="#166">166</a></td></tr
><tr id="gr_svn285_167"

><td id="167"><a href="#167">167</a></td></tr
><tr id="gr_svn285_168"

><td id="168"><a href="#168">168</a></td></tr
><tr id="gr_svn285_169"

><td id="169"><a href="#169">169</a></td></tr
><tr id="gr_svn285_170"

><td id="170"><a href="#170">170</a></td></tr
><tr id="gr_svn285_171"

><td id="171"><a href="#171">171</a></td></tr
><tr id="gr_svn285_172"

><td id="172"><a href="#172">172</a></td></tr
><tr id="gr_svn285_173"

><td id="173"><a href="#173">173</a></td></tr
><tr id="gr_svn285_174"

><td id="174"><a href="#174">174</a></td></tr
><tr id="gr_svn285_175"

><td id="175"><a href="#175">175</a></td></tr
><tr id="gr_svn285_176"

><td id="176"><a href="#176">176</a></td></tr
><tr id="gr_svn285_177"

><td id="177"><a href="#177">177</a></td></tr
><tr id="gr_svn285_178"

><td id="178"><a href="#178">178</a></td></tr
><tr id="gr_svn285_179"

><td id="179"><a href="#179">179</a></td></tr
><tr id="gr_svn285_180"

><td id="180"><a href="#180">180</a></td></tr
><tr id="gr_svn285_181"

><td id="181"><a href="#181">181</a></td></tr
><tr id="gr_svn285_182"

><td id="182"><a href="#182">182</a></td></tr
><tr id="gr_svn285_183"

><td id="183"><a href="#183">183</a></td></tr
><tr id="gr_svn285_184"

><td id="184"><a href="#184">184</a></td></tr
><tr id="gr_svn285_185"

><td id="185"><a href="#185">185</a></td></tr
><tr id="gr_svn285_186"

><td id="186"><a href="#186">186</a></td></tr
><tr id="gr_svn285_187"

><td id="187"><a href="#187">187</a></td></tr
><tr id="gr_svn285_188"

><td id="188"><a href="#188">188</a></td></tr
><tr id="gr_svn285_189"

><td id="189"><a href="#189">189</a></td></tr
><tr id="gr_svn285_190"

><td id="190"><a href="#190">190</a></td></tr
><tr id="gr_svn285_191"

><td id="191"><a href="#191">191</a></td></tr
><tr id="gr_svn285_192"

><td id="192"><a href="#192">192</a></td></tr
><tr id="gr_svn285_193"

><td id="193"><a href="#193">193</a></td></tr
><tr id="gr_svn285_194"

><td id="194"><a href="#194">194</a></td></tr
><tr id="gr_svn285_195"

><td id="195"><a href="#195">195</a></td></tr
><tr id="gr_svn285_196"

><td id="196"><a href="#196">196</a></td></tr
><tr id="gr_svn285_197"

><td id="197"><a href="#197">197</a></td></tr
><tr id="gr_svn285_198"

><td id="198"><a href="#198">198</a></td></tr
><tr id="gr_svn285_199"

><td id="199"><a href="#199">199</a></td></tr
><tr id="gr_svn285_200"

><td id="200"><a href="#200">200</a></td></tr
><tr id="gr_svn285_201"

><td id="201"><a href="#201">201</a></td></tr
><tr id="gr_svn285_202"

><td id="202"><a href="#202">202</a></td></tr
></table></pre>
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
<pre ><table id="src_table_0"><tr
id=sl_svn285_1

><td class="source">// This example demonstrates the use of shared per-block arrays<br></td></tr
><tr
id=sl_svn285_2

><td class="source">// implement an optimized dense matrix multiplication algorithm.<br></td></tr
><tr
id=sl_svn285_3

><td class="source">// Like the shared_variables.cu example, a per-block __shared__<br></td></tr
><tr
id=sl_svn285_4

><td class="source">// array acts as a &quot;bandwidth multiplier&quot; by eliminating redundant<br></td></tr
><tr
id=sl_svn285_5

><td class="source">// loads issued by neighboring threads.<br></td></tr
><tr
id=sl_svn285_6

><td class="source"><br></td></tr
><tr
id=sl_svn285_7

><td class="source">#include &lt;stdlib.h&gt;<br></td></tr
><tr
id=sl_svn285_8

><td class="source">#include &lt;vector&gt;<br></td></tr
><tr
id=sl_svn285_9

><td class="source">#include &lt;algorithm&gt;<br></td></tr
><tr
id=sl_svn285_10

><td class="source">#include &lt;iostream&gt;<br></td></tr
><tr
id=sl_svn285_11

><td class="source"><br></td></tr
><tr
id=sl_svn285_12

><td class="source">#define TILE_WIDTH 16<br></td></tr
><tr
id=sl_svn285_13

><td class="source"><br></td></tr
><tr
id=sl_svn285_14

><td class="source">// compute the number of lines of code each implementation requires<br></td></tr
><tr
id=sl_svn285_15

><td class="source">const unsigned int simple_implementation_begin = __LINE__;<br></td></tr
><tr
id=sl_svn285_16

><td class="source"><br></td></tr
><tr
id=sl_svn285_17

><td class="source">// a simple version of matrix_multiply which issues redundant loads from off-chip global memory<br></td></tr
><tr
id=sl_svn285_18

><td class="source">__global__ void matrix_multiply_simple(float *a, float *b, float *ab, size_t width)<br></td></tr
><tr
id=sl_svn285_19

><td class="source">{<br></td></tr
><tr
id=sl_svn285_20

><td class="source">  // calculate the row &amp; column index of the element<br></td></tr
><tr
id=sl_svn285_21

><td class="source">  int row = blockIdx.y*blockDim.y + threadIdx.y;<br></td></tr
><tr
id=sl_svn285_22

><td class="source">  int col = blockIdx.x*blockDim.x + threadIdx.x;<br></td></tr
><tr
id=sl_svn285_23

><td class="source"><br></td></tr
><tr
id=sl_svn285_24

><td class="source">  float result = 0;<br></td></tr
><tr
id=sl_svn285_25

><td class="source"><br></td></tr
><tr
id=sl_svn285_26

><td class="source">  // do dot product between row of a and column of b<br></td></tr
><tr
id=sl_svn285_27

><td class="source">  for(int k = 0; k &lt; width; ++k)<br></td></tr
><tr
id=sl_svn285_28

><td class="source">  {<br></td></tr
><tr
id=sl_svn285_29

><td class="source">    result += a[row*width+k] * b[k*width+col];<br></td></tr
><tr
id=sl_svn285_30

><td class="source">  }<br></td></tr
><tr
id=sl_svn285_31

><td class="source"><br></td></tr
><tr
id=sl_svn285_32

><td class="source">  // write out this thread&#39;s result<br></td></tr
><tr
id=sl_svn285_33

><td class="source">  ab[row*width+col] = result;<br></td></tr
><tr
id=sl_svn285_34

><td class="source">}<br></td></tr
><tr
id=sl_svn285_35

><td class="source">const unsigned int simple_implementation_size = __LINE__ - simple_implementation_begin;<br></td></tr
><tr
id=sl_svn285_36

><td class="source"><br></td></tr
><tr
id=sl_svn285_37

><td class="source"><br></td></tr
><tr
id=sl_svn285_38

><td class="source">const unsigned int optimized_implementation_begin = __LINE__;<br></td></tr
><tr
id=sl_svn285_39

><td class="source"><br></td></tr
><tr
id=sl_svn285_40

><td class="source">// an optimized version of matrix_multiplication which eliminates redundant loads<br></td></tr
><tr
id=sl_svn285_41

><td class="source">__global__ void matrix_multiply(float *a, float *b, float *ab, size_t width)<br></td></tr
><tr
id=sl_svn285_42

><td class="source">{<br></td></tr
><tr
id=sl_svn285_43

><td class="source">  // create shorthand names for threadIdx &amp; blockIdx<br></td></tr
><tr
id=sl_svn285_44

><td class="source">  int tx = threadIdx.x, ty = threadIdx.y;<br></td></tr
><tr
id=sl_svn285_45

><td class="source">  int bx = blockIdx.x,  by = blockIdx.y;<br></td></tr
><tr
id=sl_svn285_46

><td class="source"><br></td></tr
><tr
id=sl_svn285_47

><td class="source">  // allocate 2D tiles in __shared__ memory<br></td></tr
><tr
id=sl_svn285_48

><td class="source">  __shared__ float s_a[TILE_WIDTH][TILE_WIDTH];<br></td></tr
><tr
id=sl_svn285_49

><td class="source">  __shared__ float s_b[TILE_WIDTH][TILE_WIDTH];<br></td></tr
><tr
id=sl_svn285_50

><td class="source"><br></td></tr
><tr
id=sl_svn285_51

><td class="source">  // calculate the row &amp; column index of the element<br></td></tr
><tr
id=sl_svn285_52

><td class="source">  int row = by*blockDim.y + ty;<br></td></tr
><tr
id=sl_svn285_53

><td class="source">  int col = bx*blockDim.x + tx;<br></td></tr
><tr
id=sl_svn285_54

><td class="source"><br></td></tr
><tr
id=sl_svn285_55

><td class="source">  float result = 0;<br></td></tr
><tr
id=sl_svn285_56

><td class="source"><br></td></tr
><tr
id=sl_svn285_57

><td class="source">  // loop over the tiles of the input in phases<br></td></tr
><tr
id=sl_svn285_58

><td class="source">  for(int p = 0; p &lt; width/TILE_WIDTH; ++p)<br></td></tr
><tr
id=sl_svn285_59

><td class="source">  {<br></td></tr
><tr
id=sl_svn285_60

><td class="source">    // collaboratively load tiles into __shared__<br></td></tr
><tr
id=sl_svn285_61

><td class="source">    s_a[ty][tx] = a[row*width + (p*TILE_WIDTH + tx)];<br></td></tr
><tr
id=sl_svn285_62

><td class="source">    s_b[ty][tx] = b[(p*TILE_WIDTH + ty)*width + col];<br></td></tr
><tr
id=sl_svn285_63

><td class="source"><br></td></tr
><tr
id=sl_svn285_64

><td class="source">    // wait until all data is loaded before allowing<br></td></tr
><tr
id=sl_svn285_65

><td class="source">    // any thread in this block to continue<br></td></tr
><tr
id=sl_svn285_66

><td class="source">    __syncthreads();<br></td></tr
><tr
id=sl_svn285_67

><td class="source"><br></td></tr
><tr
id=sl_svn285_68

><td class="source">    // do dot product between row of s_a and column of s_b<br></td></tr
><tr
id=sl_svn285_69

><td class="source">    for(int k = 0; k &lt; TILE_WIDTH; ++k)<br></td></tr
><tr
id=sl_svn285_70

><td class="source">    {<br></td></tr
><tr
id=sl_svn285_71

><td class="source">      result += s_a[ty][k] * s_b[k][tx];<br></td></tr
><tr
id=sl_svn285_72

><td class="source">    }<br></td></tr
><tr
id=sl_svn285_73

><td class="source"><br></td></tr
><tr
id=sl_svn285_74

><td class="source">    // wait until all threads are finished with the data<br></td></tr
><tr
id=sl_svn285_75

><td class="source">    // before allowing any thread in this block to continue<br></td></tr
><tr
id=sl_svn285_76

><td class="source">    __syncthreads();<br></td></tr
><tr
id=sl_svn285_77

><td class="source">  }<br></td></tr
><tr
id=sl_svn285_78

><td class="source"><br></td></tr
><tr
id=sl_svn285_79

><td class="source">  // write out this thread&#39;s result<br></td></tr
><tr
id=sl_svn285_80

><td class="source">  ab[row*width+col] = result;<br></td></tr
><tr
id=sl_svn285_81

><td class="source">}<br></td></tr
><tr
id=sl_svn285_82

><td class="source">const unsigned int optimized_implementation_size = __LINE__ - optimized_implementation_begin;<br></td></tr
><tr
id=sl_svn285_83

><td class="source"><br></td></tr
><tr
id=sl_svn285_84

><td class="source"><br></td></tr
><tr
id=sl_svn285_85

><td class="source">int main(void)<br></td></tr
><tr
id=sl_svn285_86

><td class="source">{<br></td></tr
><tr
id=sl_svn285_87

><td class="source">  // create a large workload so we can easily measure the<br></td></tr
><tr
id=sl_svn285_88

><td class="source">  // performance difference of both implementations<br></td></tr
><tr
id=sl_svn285_89

><td class="source"><br></td></tr
><tr
id=sl_svn285_90

><td class="source">  // note that n measures the width of the matrix, not the number of total elements<br></td></tr
><tr
id=sl_svn285_91

><td class="source">  const size_t n = 1&lt;&lt;10;<br></td></tr
><tr
id=sl_svn285_92

><td class="source">  const dim3 block_size(TILE_WIDTH,TILE_WIDTH);<br></td></tr
><tr
id=sl_svn285_93

><td class="source">  const dim3 num_blocks(n / block_size.x, n / block_size.y);<br></td></tr
><tr
id=sl_svn285_94

><td class="source"><br></td></tr
><tr
id=sl_svn285_95

><td class="source">  // generate random input on the host<br></td></tr
><tr
id=sl_svn285_96

><td class="source">  std::vector&lt;float&gt; h_a(n*n), h_b(n*n), h_c(n*n);<br></td></tr
><tr
id=sl_svn285_97

><td class="source">  for(int i = 0; i &lt; n*n; ++i)<br></td></tr
><tr
id=sl_svn285_98

><td class="source">  {<br></td></tr
><tr
id=sl_svn285_99

><td class="source">    h_a[i] = static_cast&lt;float&gt;(rand()) / RAND_MAX;<br></td></tr
><tr
id=sl_svn285_100

><td class="source">    h_b[i] = static_cast&lt;float&gt;(rand()) / RAND_MAX;<br></td></tr
><tr
id=sl_svn285_101

><td class="source">  }<br></td></tr
><tr
id=sl_svn285_102

><td class="source"><br></td></tr
><tr
id=sl_svn285_103

><td class="source">  // allocate storage for the device<br></td></tr
><tr
id=sl_svn285_104

><td class="source">  float *d_a = 0, *d_b = 0, *d_c = 0;<br></td></tr
><tr
id=sl_svn285_105

><td class="source">  cudaMalloc((void**)&amp;d_a, sizeof(float) * n * n);<br></td></tr
><tr
id=sl_svn285_106

><td class="source">  cudaMalloc((void**)&amp;d_b, sizeof(float) * n * n);<br></td></tr
><tr
id=sl_svn285_107

><td class="source">  cudaMalloc((void**)&amp;d_c, sizeof(float) * n * n);<br></td></tr
><tr
id=sl_svn285_108

><td class="source"><br></td></tr
><tr
id=sl_svn285_109

><td class="source">  // copy input to the device<br></td></tr
><tr
id=sl_svn285_110

><td class="source">  cudaMemcpy(d_a, &amp;h_a[0], sizeof(float) * n * n, cudaMemcpyHostToDevice);<br></td></tr
><tr
id=sl_svn285_111

><td class="source">  cudaMemcpy(d_b, &amp;h_b[0], sizeof(float) * n * n, cudaMemcpyHostToDevice);<br></td></tr
><tr
id=sl_svn285_112

><td class="source"><br></td></tr
><tr
id=sl_svn285_113

><td class="source">  // time the kernel launches using CUDA events<br></td></tr
><tr
id=sl_svn285_114

><td class="source">  cudaEvent_t launch_begin, launch_end;<br></td></tr
><tr
id=sl_svn285_115

><td class="source">  cudaEventCreate(&amp;launch_begin);<br></td></tr
><tr
id=sl_svn285_116

><td class="source">  cudaEventCreate(&amp;launch_end);<br></td></tr
><tr
id=sl_svn285_117

><td class="source"><br></td></tr
><tr
id=sl_svn285_118

><td class="source">  // to get accurate timings, launch a single &quot;warm-up&quot; kernel<br></td></tr
><tr
id=sl_svn285_119

><td class="source">  matrix_multiply_simple&lt;&lt;&lt;num_blocks,block_size&gt;&gt;&gt;(d_a, d_b, d_c, n);<br></td></tr
><tr
id=sl_svn285_120

><td class="source"><br></td></tr
><tr
id=sl_svn285_121

><td class="source">  // time many kernel launches and take the average time<br></td></tr
><tr
id=sl_svn285_122

><td class="source">  const size_t num_launches = 100;<br></td></tr
><tr
id=sl_svn285_123

><td class="source">  float average_simple_time = 0;<br></td></tr
><tr
id=sl_svn285_124

><td class="source">  std::cout &lt;&lt; &quot;Timing simple implementation...&quot;;<br></td></tr
><tr
id=sl_svn285_125

><td class="source">  for(int i = 0; i &lt; num_launches; ++i)<br></td></tr
><tr
id=sl_svn285_126

><td class="source">  {<br></td></tr
><tr
id=sl_svn285_127

><td class="source">    // record a CUDA event immediately before and after the kernel launch<br></td></tr
><tr
id=sl_svn285_128

><td class="source">    cudaEventRecord(launch_begin,0);<br></td></tr
><tr
id=sl_svn285_129

><td class="source">    matrix_multiply_simple&lt;&lt;&lt;num_blocks,block_size&gt;&gt;&gt;(d_a, d_b, d_c, n);<br></td></tr
><tr
id=sl_svn285_130

><td class="source">    cudaEventRecord(launch_end,0);<br></td></tr
><tr
id=sl_svn285_131

><td class="source">    cudaEventSynchronize(launch_end);<br></td></tr
><tr
id=sl_svn285_132

><td class="source"><br></td></tr
><tr
id=sl_svn285_133

><td class="source">    // measure the time spent in the kernel<br></td></tr
><tr
id=sl_svn285_134

><td class="source">    float time = 0;<br></td></tr
><tr
id=sl_svn285_135

><td class="source">    cudaEventElapsedTime(&amp;time, launch_begin, launch_end);<br></td></tr
><tr
id=sl_svn285_136

><td class="source"><br></td></tr
><tr
id=sl_svn285_137

><td class="source">    average_simple_time += time;<br></td></tr
><tr
id=sl_svn285_138

><td class="source">  }<br></td></tr
><tr
id=sl_svn285_139

><td class="source">  average_simple_time /= num_launches;<br></td></tr
><tr
id=sl_svn285_140

><td class="source">  std::cout &lt;&lt; &quot; done.&quot; &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_141

><td class="source"><br></td></tr
><tr
id=sl_svn285_142

><td class="source">  // now time the optimized kernel<br></td></tr
><tr
id=sl_svn285_143

><td class="source"><br></td></tr
><tr
id=sl_svn285_144

><td class="source">  // again, launch a single &quot;warm-up&quot; kernel<br></td></tr
><tr
id=sl_svn285_145

><td class="source">  matrix_multiply&lt;&lt;&lt;num_blocks,block_size&gt;&gt;&gt;(d_a, d_b, d_c, n);<br></td></tr
><tr
id=sl_svn285_146

><td class="source"><br></td></tr
><tr
id=sl_svn285_147

><td class="source">  // time many kernel launches and take the average time<br></td></tr
><tr
id=sl_svn285_148

><td class="source">  float average_optimized_time = 0;<br></td></tr
><tr
id=sl_svn285_149

><td class="source">  std::cout &lt;&lt; &quot;Timing optimized implementation...&quot;;<br></td></tr
><tr
id=sl_svn285_150

><td class="source">  for(int i = 0; i &lt; num_launches; ++i)<br></td></tr
><tr
id=sl_svn285_151

><td class="source">  {<br></td></tr
><tr
id=sl_svn285_152

><td class="source">    // record a CUDA event immediately before and after the kernel launch<br></td></tr
><tr
id=sl_svn285_153

><td class="source">    cudaEventRecord(launch_begin,0);<br></td></tr
><tr
id=sl_svn285_154

><td class="source">    matrix_multiply&lt;&lt;&lt;num_blocks,block_size&gt;&gt;&gt;(d_a, d_b, d_c, n);<br></td></tr
><tr
id=sl_svn285_155

><td class="source">    cudaEventRecord(launch_end,0);<br></td></tr
><tr
id=sl_svn285_156

><td class="source">    cudaEventSynchronize(launch_end);<br></td></tr
><tr
id=sl_svn285_157

><td class="source"><br></td></tr
><tr
id=sl_svn285_158

><td class="source">    // measure the time spent in the kernel<br></td></tr
><tr
id=sl_svn285_159

><td class="source">    float time = 0;<br></td></tr
><tr
id=sl_svn285_160

><td class="source">    cudaEventElapsedTime(&amp;time, launch_begin, launch_end);<br></td></tr
><tr
id=sl_svn285_161

><td class="source"><br></td></tr
><tr
id=sl_svn285_162

><td class="source">    average_optimized_time += time;<br></td></tr
><tr
id=sl_svn285_163

><td class="source">  }<br></td></tr
><tr
id=sl_svn285_164

><td class="source">  average_optimized_time /= num_launches;<br></td></tr
><tr
id=sl_svn285_165

><td class="source">  std::cout &lt;&lt; &quot; done.&quot; &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_166

><td class="source"><br></td></tr
><tr
id=sl_svn285_167

><td class="source">  // report the effective throughput of each kernel in GFLOPS<br></td></tr
><tr
id=sl_svn285_168

><td class="source">  // the effective throughput is measured as the number of floating point operations performed per second:<br></td></tr
><tr
id=sl_svn285_169

><td class="source">  // (one mul + one add) * N^3<br></td></tr
><tr
id=sl_svn285_170

><td class="source">  float simple_throughput = static_cast&lt;float&gt;(2 * n * n * n) / (average_simple_time / 1000.0f) / 1000000000.0f;<br></td></tr
><tr
id=sl_svn285_171

><td class="source">  float optimized_throughput = static_cast&lt;float&gt;(2 * n * n * n) / (average_optimized_time / 1000.0f) / 1000000000.0f;<br></td></tr
><tr
id=sl_svn285_172

><td class="source"><br></td></tr
><tr
id=sl_svn285_173

><td class="source">  // compute throughput per line of code to measure how productive we were<br></td></tr
><tr
id=sl_svn285_174

><td class="source">  float simple_throughput_per_sloc = simple_throughput / simple_implementation_size;<br></td></tr
><tr
id=sl_svn285_175

><td class="source">  float optimized_throughput_per_sloc = optimized_throughput / optimized_implementation_size;<br></td></tr
><tr
id=sl_svn285_176

><td class="source"><br></td></tr
><tr
id=sl_svn285_177

><td class="source">  std::cout &lt;&lt; &quot;Matrix size: &quot; &lt;&lt; n &lt;&lt; &quot;x&quot; &lt;&lt; n &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_178

><td class="source">  std::cout &lt;&lt; &quot;Tile size: &quot; &lt;&lt; TILE_WIDTH &lt;&lt; &quot;x&quot; &lt;&lt; TILE_WIDTH &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_179

><td class="source">  std::cout &lt;&lt; &quot;Simple implementation SLOCs: &quot; &lt;&lt; simple_implementation_size &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_180

><td class="source">  std::cout &lt;&lt; &quot;Optimized implementation SLOCs: &quot; &lt;&lt; optimized_implementation_size &lt;&lt; std::endl &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_181

><td class="source"><br></td></tr
><tr
id=sl_svn285_182

><td class="source">  std::cout &lt;&lt; &quot;Throughput of simple kernel: &quot; &lt;&lt; simple_throughput &lt;&lt; &quot; GFLOPS&quot; &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_183

><td class="source">  std::cout &lt;&lt; &quot;Throughput of optimized kernel: &quot; &lt;&lt; optimized_throughput &lt;&lt; &quot; GFLOPS&quot; &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_184

><td class="source">  std::cout &lt;&lt; &quot;Performance improvement: &quot; &lt;&lt; optimized_throughput / simple_throughput &lt;&lt; &quot;x&quot; &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_185

><td class="source">  std::cout &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_186

><td class="source"><br></td></tr
><tr
id=sl_svn285_187

><td class="source">  std::cout &lt;&lt; &quot;Throughput of simple kernel per line of code: &quot; &lt;&lt; simple_throughput_per_sloc &lt;&lt; &quot; FLOPS/sloc&quot; &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_188

><td class="source">  std::cout &lt;&lt; &quot;Throughput of optimized kernel per line of code: &quot; &lt;&lt; optimized_throughput_per_sloc &lt;&lt; &quot; FLOPS/sloc&quot; &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_189

><td class="source">  std::cout &lt;&lt; &quot;Performance improvement per line of code: &quot; &lt;&lt; optimized_throughput_per_sloc / simple_throughput_per_sloc &lt;&lt; &quot;x&quot; &lt;&lt; std::endl;<br></td></tr
><tr
id=sl_svn285_190

><td class="source"><br></td></tr
><tr
id=sl_svn285_191

><td class="source">  // destroy the CUDA events<br></td></tr
><tr
id=sl_svn285_192

><td class="source">  cudaEventDestroy(launch_begin);<br></td></tr
><tr
id=sl_svn285_193

><td class="source">  cudaEventDestroy(launch_end);<br></td></tr
><tr
id=sl_svn285_194

><td class="source"><br></td></tr
><tr
id=sl_svn285_195

><td class="source">  // deallocate device memory<br></td></tr
><tr
id=sl_svn285_196

><td class="source">  cudaFree(d_a);<br></td></tr
><tr
id=sl_svn285_197

><td class="source">  cudaFree(d_b);<br></td></tr
><tr
id=sl_svn285_198

><td class="source">  cudaFree(d_c);<br></td></tr
><tr
id=sl_svn285_199

><td class="source"><br></td></tr
><tr
id=sl_svn285_200

><td class="source">  return 0;<br></td></tr
><tr
id=sl_svn285_201

><td class="source">}<br></td></tr
><tr
id=sl_svn285_202

><td class="source"><br></td></tr
></table></pre>
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
</td>
</tr></table>

 
<script type="text/javascript">
 var lineNumUnderMouse = -1;
 
 function gutterOver(num) {
 gutterOut();
 var newTR = document.getElementById('gr_svn285_' + num);
 if (newTR) {
 newTR.className = 'undermouse';
 }
 lineNumUnderMouse = num;
 }
 function gutterOut() {
 if (lineNumUnderMouse != -1) {
 var oldTR = document.getElementById(
 'gr_svn285_' + lineNumUnderMouse);
 if (oldTR) {
 oldTR.className = '';
 }
 lineNumUnderMouse = -1;
 }
 }
 var numsGenState = {table_base_id: 'nums_table_'};
 var srcGenState = {table_base_id: 'src_table_'};
 var alignerRunning = false;
 var startOver = false;
 function setLineNumberHeights() {
 if (alignerRunning) {
 startOver = true;
 return;
 }
 numsGenState.chunk_id = 0;
 numsGenState.table = document.getElementById('nums_table_0');
 numsGenState.row_num = 0;
 if (!numsGenState.table) {
 return; // Silently exit if no file is present.
 }
 srcGenState.chunk_id = 0;
 srcGenState.table = document.getElementById('src_table_0');
 srcGenState.row_num = 0;
 alignerRunning = true;
 continueToSetLineNumberHeights();
 }
 function rowGenerator(genState) {
 if (genState.row_num < genState.table.rows.length) {
 var currentRow = genState.table.rows[genState.row_num];
 genState.row_num++;
 return currentRow;
 }
 var newTable = document.getElementById(
 genState.table_base_id + (genState.chunk_id + 1));
 if (newTable) {
 genState.chunk_id++;
 genState.row_num = 0;
 genState.table = newTable;
 return genState.table.rows[0];
 }
 return null;
 }
 var MAX_ROWS_PER_PASS = 1000;
 function continueToSetLineNumberHeights() {
 var rowsInThisPass = 0;
 var numRow = 1;
 var srcRow = 1;
 while (numRow && srcRow && rowsInThisPass < MAX_ROWS_PER_PASS) {
 numRow = rowGenerator(numsGenState);
 srcRow = rowGenerator(srcGenState);
 rowsInThisPass++;
 if (numRow && srcRow) {
 if (numRow.offsetHeight != srcRow.offsetHeight) {
 numRow.firstChild.style.height = srcRow.offsetHeight + 'px';
 }
 }
 }
 if (rowsInThisPass >= MAX_ROWS_PER_PASS) {
 setTimeout(continueToSetLineNumberHeights, 10);
 } else {
 alignerRunning = false;
 if (startOver) {
 startOver = false;
 setTimeout(setLineNumberHeights, 500);
 }
 }
 }
 function initLineNumberHeights() {
 // Do 2 complete passes, because there can be races
 // between this code and prettify.
 startOver = true;
 setTimeout(setLineNumberHeights, 250);
 window.onresize = setLineNumberHeights;
 }
 initLineNumberHeights();
</script>

 
 
 <div id="log">
 <div style="text-align:right">
 <a class="ifCollapse" href="#" onclick="_toggleMeta(this); return false">Show details</a>
 <a class="ifExpand" href="#" onclick="_toggleMeta(this); return false">Hide details</a>
 </div>
 <div class="ifExpand">
 
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="changelog">
 <p>Change log</p>
 <div>
 <a href="/p/stanford-cs193g-sp2010/source/detail?spec=svn285&amp;r=194">r194</a>
 by jaredhoberock
 on Apr 5, 2010
 &nbsp; <a href="/p/stanford-cs193g-sp2010/source/diff?spec=svn285&r=194&amp;format=side&amp;path=/trunk/tutorials/matrix_multiplication.cu&amp;old_path=/trunk/tutorials/matrix_multiplication.cu&amp;old=">Diff</a>
 </div>
 <pre>Add matrix_multiplication example
</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/stanford-cs193g-sp2010/source/detail?r=194&spec=svn285';
 var publish_url = '/p/stanford-cs193g-sp2010/source/detail?r=194&spec=svn285#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk/tutorials/matrix_multiplication.cu');
 changed_urls.push('/p/stanford-cs193g-sp2010/source/browse/trunk/tutorials/matrix_multiplication.cu?r\x3d194\x26spec\x3dsvn285');
 
 var selected_path = '/trunk/tutorials/matrix_multiplication.cu';
 
 
 function getCurrentPageIndex() {
 for (var i = 0; i < changed_paths.length; i++) {
 if (selected_path == changed_paths[i]) {
 return i;
 }
 }
 }
 function getNextPage() {
 var i = getCurrentPageIndex();
 if (i < changed_paths.length - 1) {
 return changed_urls[i + 1];
 }
 return null;
 }
 function getPreviousPage() {
 var i = getCurrentPageIndex();
 if (i > 0) {
 return changed_urls[i - 1];
 }
 return null;
 }
 function gotoNextPage() {
 var page = getNextPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoPreviousPage() {
 var page = getPreviousPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoDetailPage() {
 window.location = detail_url;
 }
 function gotoPublishPage() {
 window.location = publish_url;
 }
</script>

 
 <style type="text/css">
 #review_nav {
 border-top: 3px solid white;
 padding-top: 6px;
 margin-top: 1em;
 }
 #review_nav td {
 vertical-align: middle;
 }
 #review_nav select {
 margin: .5em 0;
 }
 </style>
 <div id="review_nav">
 <table><tr><td>Go to:&nbsp;</td><td>
 <select name="files_in_rev" onchange="window.location=this.value">
 
 <option value="/p/stanford-cs193g-sp2010/source/browse/trunk/tutorials/matrix_multiplication.cu?r=194&amp;spec=svn285"
 selected="selected"
 >...torials/matrix_multiplication.cu</option>
 
 </select>
 </td></tr></table>
 
 
 



 
 </div>
 
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="older_bubble">
 <p>Older revisions</p>
 
 <a href="/p/stanford-cs193g-sp2010/source/list?path=/trunk/tutorials/matrix_multiplication.cu&start=194">All revisions of this file</a>
 </div>
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="fileinfo_bubble">
 <p>File info</p>
 
 <div>Size: 7648 bytes,
 202 lines</div>
 
 <div><a href="//stanford-cs193g-sp2010.googlecode.com/svn/trunk/tutorials/matrix_multiplication.cu">View raw file</a></div>
 </div>
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 </div>
 </div>


</div>

</div>
</div>


<script src="https://ssl.gstatic.com/codesite/ph/18376132045800511552/js/source_file_scripts.js"></script>

 <script type="text/javascript" src="https://ssl.gstatic.com/codesite/ph/18376132045800511552/js/kibbles.js"></script>
 <script type="text/javascript">
 var lastStop = null;
 var initialized = false;
 
 function updateCursor(next, prev) {
 if (prev && prev.element) {
 prev.element.className = 'cursor_stop cursor_hidden';
 }
 if (next && next.element) {
 next.element.className = 'cursor_stop cursor';
 lastStop = next.index;
 }
 }
 
 function pubRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initialized) {
 reloadCursors();
 }
 }
 
 function draftRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initialized) {
 reloadCursors();
 }
 }
 
 function draftDestroyed(data) {
 updateCursorForCell(data.cellId, 'nocursor');
 if (initialized) {
 reloadCursors();
 }
 }
 function reloadCursors() {
 kibbles.skipper.reset();
 loadCursors();
 if (lastStop != null) {
 kibbles.skipper.setCurrentStop(lastStop);
 }
 }
 // possibly the simplest way to insert any newly added comments
 // is to update the class of the corresponding cursor row,
 // then refresh the entire list of rows.
 function updateCursorForCell(cellId, className) {
 var cell = document.getElementById(cellId);
 // we have to go two rows back to find the cursor location
 var row = getPreviousElement(cell.parentNode);
 row.className = className;
 }
 // returns the previous element, ignores text nodes.
 function getPreviousElement(e) {
 var element = e.previousSibling;
 if (element.nodeType == 3) {
 element = element.previousSibling;
 }
 if (element && element.tagName) {
 return element;
 }
 }
 function loadCursors() {
 // register our elements with skipper
 var elements = CR_getElements('*', 'cursor_stop');
 var len = elements.length;
 for (var i = 0; i < len; i++) {
 var element = elements[i]; 
 element.className = 'cursor_stop cursor_hidden';
 kibbles.skipper.append(element);
 }
 }
 function toggleComments() {
 CR_toggleCommentDisplay();
 reloadCursors();
 }
 function keysOnLoadHandler() {
 // setup skipper
 kibbles.skipper.addStopListener(
 kibbles.skipper.LISTENER_TYPE.PRE, updateCursor);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_top', 50);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_bottom', 100);
 // Register our keys
 kibbles.skipper.addFwdKey("n");
 kibbles.skipper.addRevKey("p");
 kibbles.keys.addKeyPressListener(
 'u', function() { window.location = detail_url; });
 kibbles.keys.addKeyPressListener(
 'r', function() { window.location = detail_url + '#publish'; });
 
 kibbles.keys.addKeyPressListener('j', gotoNextPage);
 kibbles.keys.addKeyPressListener('k', gotoPreviousPage);
 
 
 }
 </script>
<script src="https://ssl.gstatic.com/codesite/ph/18376132045800511552/js/code_review_scripts.js"></script>
<script type="text/javascript">
 function showPublishInstructions() {
 var element = document.getElementById('review_instr');
 if (element) {
 element.className = 'opened';
 }
 }
 var codereviews;
 function revsOnLoadHandler() {
 // register our source container with the commenting code
 var paths = {'svn285': '/trunk/tutorials/matrix_multiplication.cu'}
 codereviews = CR_controller.setup(
 {"assetVersionPath":"https://ssl.gstatic.com/codesite/ph/18376132045800511552","token":"xgsVxMDtRHqTM3kVI14V3MX5LPc:1371808347652","projectHomeUrl":"/p/stanford-cs193g-sp2010","projectName":"stanford-cs193g-sp2010","loggedInUserEmail":"gaurav.sachin007@gmail.com","relativeBaseUrl":"","assetHostPath":"https://ssl.gstatic.com/codesite/ph","domainName":null,"profileUrl":"/u/116699586124044253698/"}, '', 'svn285', paths,
 CR_BrowseIntegrationFactory);
 
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_DRAFT_PLATE, showPublishInstructions);
 
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_PUB_PLATE, pubRevealed);
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_DRAFT_PLATE, draftRevealed);
 codereviews.registerActivityListener(CR_ActivityType.DISCARD_DRAFT_COMMENT, draftDestroyed);
 
 
 
 
 
 
 
 var initialized = true;
 reloadCursors();
 }
 window.onload = function() {keysOnLoadHandler(); revsOnLoadHandler();};

</script>
<script type="text/javascript" src="https://ssl.gstatic.com/codesite/ph/18376132045800511552/js/dit_scripts.js"></script>

 
 
 
 <script type="text/javascript" src="https://ssl.gstatic.com/codesite/ph/18376132045800511552/js/ph_core.js"></script>
 
 
 
 
</div> 

<div id="footer" dir="ltr">
 <div class="text">
 <a href="/projecthosting/terms.html">Terms</a> -
 <a href="http://www.google.com/privacy.html">Privacy</a> -
 <a href="/p/support/">Project Hosting Help</a>
 </div>
</div>
 <div class="hostedBy" style="margin-top: -20px;">
 <span style="vertical-align: top;">Powered by <a href="http://code.google.com/projecthosting/">Google Project Hosting</a></span>
 </div>

 
 


 
 </body>
</html>

