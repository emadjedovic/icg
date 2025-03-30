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
  TextHeight = 15
  object Image: TImage
    Left = 8
    Top = 8
    Width = 608
    Height = 361
    OnMouseDown = ImageMouseDown
  end
  object ButtonConvexHull: TButton
    Left = 136
    Top = 392
    Width = 91
    Height = 25
    Caption = 'Convex Hull'
    TabOrder = 0
    OnClick = ButtonConvexHullClick
  end
  object ButtonGeneratePoints: TButton
    Left = 8
    Top = 392
    Width = 112
    Height = 25
    Caption = 'Generate Points'
    TabOrder = 1
    OnClick = ButtonGeneratePointsClick
  end
  object ButtonClear: TButton
    Left = 450
    Top = 392
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
end
