xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 14;
 -17.82818;-28.92970;-1.90456;,
 -17.82818;-28.92970;1.86866;,
 -19.94597;-24.55228;1.82821;,
 -19.94597;-24.55228;-1.78142;,
 -15.78266;3.71964;2.78442;,
 -22.28516;3.68927;2.78113;,
 -22.28516;3.68927;-2.73433;,
 -15.78266;3.71964;-2.73102;,
 4.85595;3.79460;-2.72772;,
 4.92383;-2.54803;-2.72772;,
 -16.19663;-2.73733;-2.52847;,
 4.85595;3.79460;2.78773;,
 4.92383;-2.54803;2.78773;,
 -16.20232;-2.82733;2.58361;;
 
 11;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,3,2,5;,
 4;4,7,6,5;,
 4;7,8,9,10;,
 4;8,11,12,9;,
 4;11,4,13,12;,
 4;4,11,8,7;,
 4;10,9,12,13;,
 4;13,1,0,10;,
 4;0,3,6,7;;
 
 MeshMaterialList {
  4;
  11;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.960000;0.960000;0.960000;0.760000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.663000;0.663000;0.663000;1.000000;;
   5.000000;
   0.200000;0.200000;0.200000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.545600;0.545600;0.545600;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  15;
  -0.004151;0.999991;0.000000;,
  -0.996587;-0.082545;0.000000;,
  -0.900185;-0.435508;0.000000;,
  -0.964667;-0.263473;0.000000;,
  -0.019470;-0.021894;0.999571;,
  -0.034225;-0.028748;0.999001;,
  -0.004497;-0.015384;-0.999872;,
  0.999943;0.010702;0.000000;,
  -0.004711;-0.015034;0.999876;,
  -0.004670;0.999989;0.000000;,
  -0.026449;-0.020903;-0.999432;,
  -0.003632;0.999993;0.000000;,
  0.011175;-0.999899;-0.008793;,
  0.998066;-0.062169;0.000008;,
  -0.048387;-0.026412;-0.998479;;
  11;
  4;2,2,3,3;,
  4;5,4,5,5;,
  4;1,3,3,1;,
  4;0,0,9,9;,
  4;10,6,6,6;,
  4;7,7,7,7;,
  4;8,4,8,8;,
  4;0,11,11,0;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,10;;
 }
}
