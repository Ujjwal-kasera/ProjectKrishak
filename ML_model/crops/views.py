from django.shortcuts import render
from .Serializers import UserSerializer
from rest_framework.views import APIView
from .models import *
from .Serializers import *
from django.http import HttpResponse
from rest_framework.response import Response
from django.shortcuts import render
from django.http import HttpResponse
import joblib
import numpy as np
def result(request):
   print("8888888888888888888888888888888888888888")
   cls=joblib.load('C:/Users/DELL/Downloads/model.pkl')
   lis=[]
   lis.append(12)
   lis.append(20)
   lis.append(50)
   lis.append(30)
   lis.append(50)
   lis.append(7.5)
   lis.append(50)
   #print(lis)
   data_array = np.asarray(lis)
   arr= data_array.reshape(1,-1)
   ans = cls.predict(arr)
   print('====================',ans)
   return HttpResponse(f'Suitable Crop is {ans}')
# Create your views here.
class dataApi(APIView):
    def get(self,request):
        data=Data.objects.all()
        seri=UserSerializer(data,many=True)
        return Response(seri.data)
    def post(self,request):
        print("*******************",request.data["n"])
        Data.objects.create(n_value=request.data['n'],p_value=request.data['p'],k_value=request.data['k'],temp=request.data['t'],humidity=request.data['h'])
        data=Data.objects.all()
        seri=UserSerializer(data,many=True)
        return Response(seri.data)

    
def hello(request):
    return render(request,'index.html')
