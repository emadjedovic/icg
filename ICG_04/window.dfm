object Triangulation: TTriangulation
  Left = 0
  Top = 0
  Caption = 'Triangulation'
  ClientHeight = 452
  ClientWidth = 643
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 15
  object Image: TImage
    Left = 6
    Top = 8
    Width = 629
    Height = 377
    OnMouseDown = ImageMouseDown
  end
  object ButtonTriangulation: TButton
    Left = 24
    Top = 408
    Width = 75
    Height = 25
    Caption = 'Triangulation'
    TabOrder = 0
    OnClick = ButtonTriangulationClick
  end
  object ButtonImprove: TButton
    Left = 216
    Top = 408
    Width = 75
    Height = 25
    Caption = 'Improve'
    TabOrder = 1
    OnClick = ButtonImproveClick
  end
  object ButtonClear: TButton
    Left = 120
    Top = 408
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 2
    OnClick = ButtonClearClick
  end
  object CheckBoxProcedure: TCheckBox
    Left = 528
    Top = 412
    Width = 97
    Height = 17
    Caption = 'Procedure'
    TabOrder = 3
  end
end
