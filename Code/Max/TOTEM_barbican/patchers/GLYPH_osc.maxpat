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
		"rect" : [ 373.0, 102.0, 1023.0, 900.0 ],
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
					"id" : "obj-40",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 667.5, 793.401001, 195.0, 22.0 ],
					"style" : "",
					"text" : "prepend /glyph/glyph_sub_rotation"
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
					"id" : "obj-41",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 667.5, 766.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 56.0, 189.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[22]",
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
					"varname" : "gatepct[16]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-42",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 714.0, 766.401001, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 98.0, 186.401001, 160.5, 17.0 ],
					"style" : "",
					"text" : "glyph_sub_rotation",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-43",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 622.5, 718.401001, 192.0, 22.0 ],
					"style" : "",
					"text" : "prepend /glyph/glyph_top_rotation"
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
					"id" : "obj-44",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 622.5, 691.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 56.0, 174.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[23]",
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
					"varname" : "gatepct[17]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-45",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 669.0, 691.401001, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 98.0, 171.401001, 160.5, 17.0 ],
					"style" : "",
					"text" : "glyph_top_rotation",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 577.5, 643.401001, 177.0, 22.0 ],
					"style" : "",
					"text" : "prepend /glyph/glyph_sub_type"
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
					"id" : "obj-38",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 577.5, 616.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 56.0, 159.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[21]",
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
					"varname" : "gatepct[5]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-39",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 624.0, 616.401001, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 98.0, 156.401001, 160.5, 17.0 ],
					"style" : "",
					"text" : "glyph_sub_type",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-34",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 532.5, 568.401001, 175.0, 22.0 ],
					"style" : "",
					"text" : "prepend /glyph/glyph_top_type"
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
					"patching_rect" : [ 532.5, 541.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 56.0, 144.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[17]",
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
					"varname" : "gatepct[1]"
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
					"patching_rect" : [ 579.0, 541.401001, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 98.0, 141.401001, 160.5, 17.0 ],
					"style" : "",
					"text" : "glyph_top_type",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 185.0, 521.0, 75.0, 22.0 ],
					"style" : "",
					"text" : "speedlim 30"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-17",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 487.5, 493.401001, 228.0, 22.0 ],
					"style" : "",
					"text" : "prepend /glyph/glyph_sub_mutation_rate"
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
					"id" : "obj-18",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 487.5, 466.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 56.0, 129.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[20]",
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
					"varname" : "gatepct[4]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-19",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 534.0, 466.401001, 112.0, 27.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 98.0, 126.401001, 160.5, 17.0 ],
					"style" : "",
					"text" : "glyph_sub_mutation_rate",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 457.5, 431.0, 225.0, 22.0 ],
					"style" : "",
					"text" : "prepend /glyph/glyph_top_mutation_rate"
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
					"id" : "obj-14",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 457.5, 406.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 56.0, 114.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[19]",
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
					"varname" : "gatepct[3]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-15",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 504.0, 406.401001, 112.0, 27.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 98.0, 111.401001, 160.5, 17.0 ],
					"style" : "",
					"text" : "glyph_top_mutation_rate",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 412.5, 371.0, 261.0, 22.0 ],
					"style" : "",
					"text" : "prepend /glyph/glyph_sub_activation_threshold"
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
					"patching_rect" : [ 412.5, 346.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 56.0, 99.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[18]",
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
					"varname" : "gatepct[2]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-11",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 459.0, 346.401001, 112.0, 27.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 98.0, 98.401001, 160.5, 17.0 ],
					"style" : "",
					"text" : "glyph_sub_activation_threshold",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 550.0, 975.0, 137.0, 22.0 ],
					"style" : "",
					"text" : "udpsend localhost 7512"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 550.0, 945.0, 81.0, 22.0 ],
					"style" : "",
					"text" : "r #0-udpsend"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 370.0, 975.0, 136.0, 22.0 ],
					"style" : "",
					"text" : "udpsend localhost 7511"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 370.0, 945.0, 81.0, 22.0 ],
					"style" : "",
					"text" : "r #0-udpsend"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-33",
					"maxclass" : "newobj",
					"numinlets" : 10,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 200.0, 446.0, 113.5, 22.0 ],
					"style" : "",
					"text" : "pak f f f f f f f f f f"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-31",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 303.0, 235.028915, 20.0, 13.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-32",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 290.5, 222.028915, 20.0, 13.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-24",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 280.0, 235.028915, 20.0, 13.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-28",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 267.5, 222.028915, 20.0, 13.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-29",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 257.0, 235.028915, 20.0, 13.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-30",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 246.5, 222.028915, 20.0, 13.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-22",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 235.0, 235.028915, 20.0, 13.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-23",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 222.5, 222.028915, 20.0, 13.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-21",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 212.0, 235.028915, 20.0, 13.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 4.0,
					"id" : "obj-20",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 201.5, 222.028915, 20.0, 13.0 ],
					"style" : "",
					"text" : "set $1"
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
					"id" : "obj-86",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 336.0, 422.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.0, 69.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[16]",
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
					"varname" : "gatepct[15]"
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
					"id" : "obj-83",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 318.0, 409.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.0, 84.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[13]",
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
					"id" : "obj-84",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 303.0, 394.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.0, 99.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[14]",
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
					"varname" : "gatepct[13]"
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
					"id" : "obj-85",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 288.0, 379.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.0, 114.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[15]",
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
					"varname" : "gatepct[14]"
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
					"id" : "obj-80",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 273.0, 364.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.0, 129.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[10]",
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
					"id" : "obj-81",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 258.0, 349.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.0, 144.401001, 36.0, 15.0 ],
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
					"id" : "obj-82",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 243.0, 334.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.0, 159.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[12]",
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
					"id" : "obj-79",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 228.0, 319.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.0, 174.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[9]",
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
					"id" : "obj-78",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 213.0, 304.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.0, 189.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[8]",
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
					"id" : "obj-76",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 198.0, 289.401001, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.0, 204.401001, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "gatepct[7]",
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
					"varname" : "gatepct[6]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-77",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 10,
					"outlettype" : [ "float", "float", "float", "float", "float", "float", "float", "float", "float", "float" ],
					"patching_rect" : [ 200.0, 191.401001, 116.0, 22.0 ],
					"style" : "",
					"text" : "unpack f f f f f f f f f f"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 185.0, 491.0, 158.0, 22.0 ],
					"style" : "",
					"text" : "prepend /glyph/glyph_alpha"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial Bold",
					"fontsize" : 9.0,
					"id" : "obj-7",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 155.5, 408.401001, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 6.0, 46.742615, 71.0, 17.0 ],
					"style" : "",
					"text" : "glyph_alpha",
					"textcolor" : [ 0.862745, 0.870588, 0.878431, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"linecount" : 2,
					"maxclass" : "newobj",
					"numinlets" : 10,
					"numoutlets" : 10,
					"outlettype" : [ "", "", "", "", "", "", "", "", "", "" ],
					"patching_rect" : [ 185.0, 118.0, 753.0, 35.0 ],
					"style" : "",
					"text" : "route glyph_alpha glyph_trig_sensibility glyph_sub_activation_threshold glyph_top_mutation_rate glyph_sub_mutation_rate glyph_top_type glyph_sub_type glyph_top_rotation glyph_sub_rotation"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-3",
					"index" : 0,
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 185.0, 78.0, 30.0, 30.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 185.0, 919.598999, 83.0, 22.0 ],
					"style" : "",
					"text" : "s #0-udpsend"
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
					"patching_rect" : [ 87.554688, 6.910889, 112.0, 17.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 89.0, 8.742615, 67.0, 17.0 ],
					"style" : "",
					"text" : "GLYPH_osc",
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ]
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
					"patching_rect" : [ 29.852829, 14.033447, 37.0, 5.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 2.949341, 4.3974, 244.550659, 223.003601 ],
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
					"patching_rect" : [ 4.0, 6.910889, 12.0, 188.0 ],
					"presentation" : 1,
					"presentation_rect" : [ -0.239624, 0.338165, 251.739624, 230.658203 ],
					"proportion" : 0.39,
					"style" : ""
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-76", 0 ],
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-78", 0 ],
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-82", 0 ],
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"source" : [ "obj-23", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-84", 0 ],
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 0 ],
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-80", 0 ],
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-81", 0 ],
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-86", 0 ],
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 0 ],
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"order" : 1,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"source" : [ "obj-4", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"source" : [ "obj-4", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"source" : [ "obj-4", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-38", 0 ],
					"source" : [ "obj-4", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-41", 0 ],
					"source" : [ "obj-4", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"source" : [ "obj-4", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-77", 0 ],
					"order" : 0,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"source" : [ "obj-4", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-40", 0 ],
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-43", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 0 ],
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-76", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"source" : [ "obj-77", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 0 ],
					"source" : [ "obj-77", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-22", 0 ],
					"source" : [ "obj-77", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-23", 0 ],
					"source" : [ "obj-77", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"source" : [ "obj-77", 7 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 0 ],
					"source" : [ "obj-77", 6 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"source" : [ "obj-77", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"source" : [ "obj-77", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"source" : [ "obj-77", 9 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"source" : [ "obj-77", 8 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 1 ],
					"source" : [ "obj-78", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 2 ],
					"source" : [ "obj-79", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 5 ],
					"source" : [ "obj-80", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 4 ],
					"source" : [ "obj-81", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 3 ],
					"source" : [ "obj-82", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 8 ],
					"source" : [ "obj-83", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 7 ],
					"source" : [ "obj-84", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 6 ],
					"source" : [ "obj-85", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 9 ],
					"source" : [ "obj-86", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-86" : [ "gatepct[16]", "gatepct", 0 ],
			"obj-82" : [ "gatepct[12]", "gatepct", 0 ],
			"obj-80" : [ "gatepct[10]", "gatepct", 0 ],
			"obj-38" : [ "gatepct[21]", "gatepct", 0 ],
			"obj-35" : [ "gatepct[17]", "gatepct", 0 ],
			"obj-18" : [ "gatepct[20]", "gatepct", 0 ],
			"obj-14" : [ "gatepct[19]", "gatepct", 0 ],
			"obj-8" : [ "gatepct[18]", "gatepct", 0 ],
			"obj-79" : [ "gatepct[9]", "gatepct", 0 ],
			"obj-84" : [ "gatepct[14]", "gatepct", 0 ],
			"obj-83" : [ "gatepct[13]", "gatepct", 0 ],
			"obj-44" : [ "gatepct[23]", "gatepct", 0 ],
			"obj-76" : [ "gatepct[7]", "gatepct", 0 ],
			"obj-41" : [ "gatepct[22]", "gatepct", 0 ],
			"obj-85" : [ "gatepct[15]", "gatepct", 0 ],
			"obj-81" : [ "gatepct[11]", "gatepct", 0 ],
			"obj-78" : [ "gatepct[8]", "gatepct", 0 ]
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
