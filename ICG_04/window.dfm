object App: TApp
  Left = 0
  Top = 0
  Caption = 'Divide & Conquer - Convex Hull'
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu
  TextHeight = 15
  object Image: TImage
    Left = 88
    Top = 8
    Width = 513
    Height = 361
    OnClick = ImageClick
  end
  object ButtonConvexHull: TButton
    Left = 88
    Top = 392
    Width = 91
    Height = 25
    Caption = 'Convex Hull'
    TabOrder = 0
    OnClick = ButtonConvexHullClick
  end
  object ButtonGeneratePoints: TButton
    Left = 202
    Top = 392
    Width = 112
    Height = 25
    Caption = 'Generate Points'
    TabOrder = 1
    OnClick = ButtonGeneratePointsClick
  end
  object ButtonClear: TButton
    Left = 18
    Top = 80
    Width = 55
    Height = 25
    Caption = 'Clear'
    TabOrder = 2
    OnClick = ButtonClearClick
  end
  object CheckBoxProcedure: TCheckBox
    Left = 519
    Top = 396
    Width = 97
    Height = 17
    Caption = 'Procedure'
    Checked = True
    State = cbChecked
    TabOrder = 3
    OnClick = CheckBoxProcedureClick
  end
  object MainMenu: TMainMenu
    Left = 32
    Top = 8
  end
end
