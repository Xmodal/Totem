{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 3,
			"revision" : 4,
			"architecture" : "x86",
			"modernui" : 1
		}
,
		"rect" : [ 59.0, 104.0, 789.0, 597.0 ],
		"bglocked" : 0,
		"openinpresentation" : 1,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-45",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "float" ],
					"patching_rect" : [ 315.0, 139.0, 31.0, 22.0 ],
					"style" : "",
					"text" : "t b f"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-44",
					"maxclass" : "multislider",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 428.111115, 488.0, 211.0, 140.0 ],
					"setminmax" : [ -100.0, 100.0 ],
					"size" : 10,
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-43",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 327.0, 179.0, 53.0, 22.0 ],
					"style" : "",
					"text" : "pow 0.5"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-42",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 165.0, 291.0, 43.0, 22.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-40",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 145.0, 324.0, 55.0, 22.0 ],
					"style" : "",
					"text" : "prepend"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-37",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 368.555542, 103.0, 49.388885, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 261.0, 9.742615, 25.0, 17.0 ],
					"style" : "",
					"text" : "Q",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-36",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 158.555542, 103.0, 53.111122, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 53.0, 9.742615, 53.0, 17.0 ],
					"style" : "",
					"text" : "signal",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-38",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 278.555542, 103.0, 49.388885, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 160.0, 7.742615, 51.0, 17.0 ],
					"style" : "",
					"text" : "center",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-33",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 331.0, 103.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 220.0, 9.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[11]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmax" : 1.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[11]"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-34",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 240.333328, 103.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 118.0, 9.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[12]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 1,
							"parameter_mmax" : 10.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 0,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[12]"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-35",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 121.0, 103.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 10.0, 9.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[13]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -500.0,
							"parameter_mmax" : 500.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[13]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-32",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "int" ],
					"patching_rect" : [ 145.0, 230.0, 39.0, 22.0 ],
					"style" : "",
					"text" : "t i i"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "newobj",
					"numinlets" : 11,
					"numoutlets" : 11,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "", "" ],
					"patching_rect" : [ 145.0, 353.0, 352.888855, 22.0 ],
					"style" : "",
					"text" : "route 1 2 3 4 5 6 7 8 9 10"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-29",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 367.944427, 65.0, 46.0, 20.0 ],
					"style" : "",
					"text" : "Q"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 281.944427, 65.0, 46.0, 20.0 ],
					"style" : "",
					"text" : "center"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 158.166656, 65.0, 53.500008, 20.0 ],
					"style" : "",
					"text" : "signal"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-17",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 3,
					"outlettype" : [ "bang", "bang", "int" ],
					"patching_rect" : [ 121.0, 202.910889, 43.0, 22.0 ],
					"style" : "",
					"text" : "uzi 10"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "float" ],
					"patching_rect" : [ 121.0, 172.0, 90.666664, 22.0 ],
					"style" : "",
					"text" : "t b f"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 121.0, 140.0, 69.0, 22.0 ],
					"style" : "",
					"text" : "speedlim 5"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "newobj",
					"numinlets" : 4,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 145.0, 258.0, 182.0, 22.0 ],
					"style" : "",
					"text" : "expr $f2*(1-abs($f3-$f1)*(1-$f4))"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-12",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 445.5, 390.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 333.0, 39.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[9]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -727379968.0,
							"parameter_mmax" : 1215752192.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[9]"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-13",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 412.111115, 390.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 297.0, 39.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[10]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -727379968.0,
							"parameter_mmax" : 1215752192.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[10]"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-8",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 378.722198, 390.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 261.0, 39.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[4]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -727379968.0,
							"parameter_mmax" : 1215752192.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[4]"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-9",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 345.333344, 390.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 226.0, 39.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[7]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -727379968.0,
							"parameter_mmax" : 1215752192.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[6]"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-10",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 311.944427, 390.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 190.0, 39.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[8]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -727379968.0,
							"parameter_mmax" : 1215752192.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[7]"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-11",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 278.555542, 390.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 154.0, 39.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[5]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -727379968.0,
							"parameter_mmax" : 1215752192.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[8]"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-2",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 245.166656, 390.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 118.0, 39.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[2]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -727379968.0,
							"parameter_mmax" : 1215752192.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[2]"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-6",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 211.777771, 390.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 81.0, 39.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[3]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -727379968.0,
							"parameter_mmax" : 1215752192.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[3]"
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-1",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 178.388885, 390.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 45.0, 39.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[1]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -727379968.0,
							"parameter_mmax" : 1215752192.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[1]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-27",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 102.554688, 21.910889, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 297.0, 8.742615, 67.0, 17.0 ],
					"style" : "",
					"text" : "SPREADING",
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"activebgcolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"activeslidercolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor" : [ 0.278431, 0.839216, 1.0, 1.0 ],
					"activetricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"annotation" : "",
					"appearance" : 1,
					"bordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"focusbordercolor" : [ 1.0, 1.0, 1.0, 0.3 ],
					"id" : "obj-63",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 145.0, 390.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 9.0, 39.742615, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[6]",
							"parameter_shortname" : "gatepct",
							"parameter_type" : 0,
							"parameter_mmin" : -727379968.0,
							"parameter_mmax" : 1215752192.0,
							"parameter_initial" : [ 1.0 ],
							"parameter_unitstyle" : 1,
							"parameter_defer" : 1
						}

					}
,
					"textcolor" : [ 0.094118, 0.117647, 0.137255, 1.0 ],
					"tricolor2" : [ 1.0, 1.0, 1.0, 0.301961 ],
					"varname" : "gatepct[5]"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-18",
					"index" : 0,
					"maxclass" : "outlet",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 145.0, 450.0, 30.0, 30.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 10,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 145.0, 418.0, 319.5, 22.0 ],
					"style" : "",
					"text" : "pak f f f f f f f f f f"
				}

			}
, 			{
				"box" : 				{
					"comment" : "spreading Q",
					"id" : "obj-5",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 331.0, 60.0, 30.0, 30.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"comment" : "center box",
					"id" : "obj-4",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 240.333328, 60.0, 30.0, 30.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"comment" : "signal",
					"id" : "obj-3",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 121.0, 60.0, 30.0, 30.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"angle" : 0.0,
					"background" : 1,
					"bgcolor" : [ 0.367404, 0.389405, 0.430238, 1.0 ],
					"id" : "obj-25",
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 44.852829, 29.033447, 37.0, 5.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2.949341, 5.3974, 371.550659, 56.003601 ],
					"proportion" : 0.39,
					"rounded" : 0,
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"angle" : 270.0,
					"background" : 1,
					"bgcolor" : [ 0.862745, 0.870588, 0.878431, 0.5 ],
					"border" : 2,
					"bordercolor" : [ 0.65098, 0.666667, 0.662745, 1.0 ],
					"id" : "obj-26",
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 19.0, 21.910889, 12.0, 188.0 ],
					"presentation" : 1,
					"presentation_rect" : [ -0.239624, 1.338165, 378.739624, 63.658203 ],
					"proportion" : 0.39,
					"style" : ""
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 1 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 5 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 4 ],
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 9 ],
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 8 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-40", 0 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 1 ],
					"source" : [ "obj-16", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"source" : [ "obj-17", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 3 ],
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-31", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"source" : [ "obj-31", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"source" : [ "obj-31", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"source" : [ "obj-31", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"source" : [ "obj-31", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-31", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"source" : [ "obj-31", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-63", 0 ],
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"source" : [ "obj-31", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-31", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 0 ],
					"source" : [ "obj-32", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 0 ],
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 2 ],
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 0 ],
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-40", 0 ],
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 3 ],
					"source" : [ "obj-43", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 0 ],
					"source" : [ "obj-45", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 2 ],
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"order" : 1,
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"order" : 0,
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 7 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 6 ],
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-9" : [ "gatepct[7]", "gatepct", 0 ],
			"obj-2" : [ "gatepct[2]", "gatepct", 0 ],
			"obj-1" : [ "gatepct[1]", "gatepct", 0 ],
			"obj-33" : [ "gatepct[11]", "gatepct", 0 ],
			"obj-10" : [ "gatepct[8]", "gatepct", 0 ],
			"obj-34" : [ "gatepct[12]", "gatepct", 0 ],
			"obj-13" : [ "gatepct[10]", "gatepct", 0 ],
			"obj-11" : [ "gatepct[5]", "gatepct", 0 ],
			"obj-8" : [ "gatepct[4]", "gatepct", 0 ],
			"obj-6" : [ "gatepct[3]", "gatepct", 0 ],
			"obj-12" : [ "gatepct[9]", "gatepct", 0 ],
			"obj-63" : [ "gatepct[6]", "gatepct", 0 ],
			"obj-35" : [ "gatepct[13]", "gatepct", 0 ]
		}
,
		"dependency_cache" : [  ],
		"autosave" : 0,
		"styles" : [ 			{
				"name" : "AudioStatus_Menu",
				"default" : 				{
					"bgfillcolor" : 					{
						"type" : "color",
						"color" : [ 0.294118, 0.313726, 0.337255, 1 ],
						"color1" : [ 0.454902, 0.462745, 0.482353, 0.0 ],
						"color2" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"angle" : 270.0,
						"proportion" : 0.39,
						"autogradient" : 0
					}

				}
,
				"parentstyle" : "",
				"multi" : 0
			}
 ]
	}

}
