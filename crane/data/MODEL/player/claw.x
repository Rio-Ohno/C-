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
 12;
 1.34597;-2.34774;-0.05930;,
 1.35370;-2.34615;1.36423;,
 1.72351;-3.11473;-0.05930;,
 1.33506;-2.35009;1.95390;,
 1.35370;-2.34615;-1.48284;,
 1.33506;-2.35009;-2.07249;,
 0.87646;-1.45524;2.94560;,
 0.87331;-1.44774;-0.05930;,
 0.87281;-1.43959;-3.06777;,
 -1.68513;3.03383;-0.05930;,
 -1.68293;3.06528;-1.90456;,
 -1.68293;3.06528;1.86866;;
 
 24;
 3;0,1,2;,
 3;1,3,2;,
 3;3,1,2;,
 3;1,0,2;,
 3;0,4,2;,
 3;4,5,2;,
 3;5,4,2;,
 3;4,0,2;,
 4;6,1,0,7;,
 4;7,0,1,6;,
 4;8,4,0,7;,
 4;7,0,4,8;,
 3;9,6,7;,
 3;9,7,6;,
 3;9,8,7;,
 3;9,7,8;,
 3;8,5,4;,
 3;8,9,10;,
 3;8,4,5;,
 3;8,10,9;,
 3;6,3,1;,
 3;6,9,11;,
 3;6,1,3;,
 3;6,11,9;;
 
 MeshMaterialList {
  4;
  24;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
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
  24;
  -0.870778;-0.491586;-0.009413;,
  0.871089;0.491042;-0.009001;,
  0.869713;0.493558;0.000485;,
  0.890564;0.454857;0.000173;,
  0.902204;0.431089;0.013820;,
  0.913033;0.406662;0.031581;,
  -0.902684;-0.430088;0.013654;,
  -0.913737;-0.405075;0.031594;,
  0.910444;0.413633;-0.000000;,
  0.876203;0.481941;0.000554;,
  0.882068;0.471095;0.005053;,
  -0.882519;-0.470257;0.004403;,
  -0.913033;-0.406662;-0.031581;,
  -0.902204;-0.431089;-0.013820;,
  -0.910444;-0.413633;0.000000;,
  -0.890564;-0.454857;-0.000173;,
  0.913737;0.405075;-0.031594;,
  0.902684;0.430088;-0.013654;,
  -0.876203;-0.481941;-0.000554;,
  -0.882068;-0.471095;-0.005053;,
  0.882519;0.470257;-0.004403;,
  -0.869713;-0.493558;-0.000485;,
  0.870778;0.491586;0.009413;,
  -0.871089;-0.491042;0.009001;;
  24;
  3;3,4,8;,
  3;4,5,8;,
  3;12,13,14;,
  3;13,15,14;,
  3;15,6,14;,
  3;6,7,14;,
  3;16,17,8;,
  3;17,3,8;,
  4;10,4,3,9;,
  4;18,15,13,19;,
  4;11,6,15,18;,
  4;9,3,17,20;,
  3;2,10,9;,
  3;21,18,19;,
  3;21,11,18;,
  3;2,9,20;,
  3;11,7,6;,
  3;11,21,0;,
  3;20,17,16;,
  3;20,22,2;,
  3;10,5,4;,
  3;10,2,1;,
  3;19,13,12;,
  3;19,23,21;;
 }
}
