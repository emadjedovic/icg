object MyApp: TMyApp
  Left = 0
  Top = 0
  Caption = 'MyApp'
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
    Top = 16
    Width = 473
    Height = 417
    OnMouseDown = ImageMouseDown
  end
  object SimplePath: TButton
    Left = 496
    Top = 16
    Width = 97
    Height = 33
    Caption = 'Simple Path'
    TabOrder = 0
    OnClick = SimplePathClick
  end
  object ConvexHull: TButton
    Left = 496
    Top = 65
    Width = 97
    Height = 33
    Caption = 'Convex Hull'
    TabOrder = 1
    OnClick = ConvexHullClick
  end
  object Clear: TButton
    Left = 496
    Top = 112
    Width = 97
    Height = 33
    Caption = 'Clear'
    TabOrder = 2
    OnClick = ClearClick
  end
end
