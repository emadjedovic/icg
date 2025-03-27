object GrahamScan: TGrahamScan
  Left = 0
  Top = 0
  Caption = 'Graham Scan'
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnActivate = FormActivate
  TextHeight = 15
  object Image: TImage
    Left = 8
    Top = 8
    Width = 608
    Height = 377
    OnMouseDown = ImageMouseDown
  end
  object GeneratePointsButton: TButton
    Left = 8
    Top = 408
    Width = 121
    Height = 25
    Caption = 'Generate Points'
    TabOrder = 0
    OnClick = GeneratePointsButtonClick
  end
  object ClearButton: TButton
    Left = 152
    Top = 408
    Width = 113
    Height = 25
    Caption = 'Clear'
    TabOrder = 1
    OnClick = ClearButtonClick
  end
  object GrahamScanButton: TButton
    Left = 288
    Top = 408
    Width = 113
    Height = 25
    Caption = 'Graham Scan'
    TabOrder = 2
    OnClick = GrahamScanButtonClick
  end
  object Edit: TEdit
    Left = 472
    Top = 408
    Width = 144
    Height = 25
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    Text = '20'
    TextHint = 'Number of points to generate.'
  end
end
