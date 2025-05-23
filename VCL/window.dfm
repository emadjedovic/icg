object ICG_app: TICG_app
  Left = 0
  Top = 0
  Caption = 'ICG_app'
  ClientHeight = 585
  ClientWidth = 896
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Image: TImage
    Left = 8
    Top = 8
    Width = 713
    Height = 513
    OnMouseDown = ImageMouseDown
  end
  object ButtonSimplePolygon: TButton
    Left = 8
    Top = 544
    Width = 113
    Height = 33
    Caption = 'Simple Polygon'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = ButtonSimplePolygonClick
  end
  object ButtonDoSegmentsIntersect: TButton
    Left = 135
    Top = 544
    Width = 146
    Height = 33
    Caption = 'Do Segments Intersect?'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = ButtonDoSegmentsIntersectClick
  end
  object ButtonGiftWrapping: TButton
    Left = 295
    Top = 544
    Width = 98
    Height = 33
    Caption = 'Gift Wrapping'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = ButtonGiftWrappingClick
  end
  object ButtonClear: TButton
    Left = 737
    Top = 288
    Width = 72
    Height = 33
    Caption = 'Clear'
    TabOrder = 3
    OnClick = ButtonClearClick
  end
  object EditGeneratePoints: TEdit
    Left = 735
    Top = 24
    Width = 113
    Height = 23
    Hint = 'Number of points to generate.'
    ParentShowHint = False
    ShowHint = False
    TabOrder = 4
    Text = '20'
  end
  object ButtonGeneratePoints: TButton
    Left = 736
    Top = 64
    Width = 112
    Height = 33
    Caption = 'Generate Points'
    TabOrder = 5
    OnClick = ButtonGeneratePointsClick
  end
  object RadioAddPoint: TRadioButton
    Left = 736
    Top = 128
    Width = 82
    Height = 17
    Caption = 'Add Point'
    Color = clWhite
    ParentColor = False
    TabOrder = 6
  end
  object RadioAddSegment: TRadioButton
    Left = 736
    Top = 167
    Width = 98
    Height = 17
    Caption = 'Add Segment'
    Color = clWhite
    ParentColor = False
    TabOrder = 7
  end
  object RadioPointInCH: TRadioButton
    Left = 736
    Top = 208
    Width = 152
    Height = 17
    Caption = 'Point In Convex Hull?'
    TabOrder = 8
  end
  object ButtonGrahamScan: TButton
    Left = 408
    Top = 544
    Width = 97
    Height = 33
    Caption = 'Graham Scan'
    TabOrder = 9
    OnClick = ButtonGrahamScanClick
  end
  object RadioDrawTangents: TRadioButton
    Left = 737
    Top = 248
    Width = 113
    Height = 17
    Caption = 'Draw Tangents'
    TabOrder = 10
  end
  object ButtonIncrementalConvex: TButton
    Left = 519
    Top = 544
    Width = 130
    Height = 33
    Caption = 'Incremental Convex'
    TabOrder = 11
    OnClick = ButtonIncrementalConvexClick
  end
end
