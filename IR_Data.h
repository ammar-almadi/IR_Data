/*
 Name:		IR_Data.h
 Created:	2/5/2025 8:37:42 PM
 Author:	AMMAR
 Editor:	http://www.visualmicro.com
*/

#ifndef _IR_Data_h
#define _IR_Data_h


#ifdef ESP32  
#include <WiFi.h>  
#include <HTTPClient.h>  
#else  
#include <ESP8266WiFi.h>  
#include <ESP8266HTTPClient.h>  
#endif  
#include <ArduinoJson.h>  
#include <ArduinoJson.hpp>

class APIClient
{
public:
    String Brand_getAll()
    {
        return httpGet("ir-data.somee.com/API/BrandAll");
    }
    String Brand_ById(int id)
    {
        return httpGet("ir-data.somee.com/API/BrandFindById?id=" + String(id));
    }
    String Brand_ByName(const String& brandName)
    {
        return httpGet("ir-data.somee.com/API/BrandFindByBrandName?BrandName=" + brandName);
    }

    String Device_getAll()
    {
        return httpGet("ir-data.somee.com/API/DeviceAll");
    }
    String Device_ById(int id)
    {
        return httpGet("ir-data.somee.com/API/DeviceFindById?id=" + String(id));
    }
    String Device_ByModel(const String& model)
    {
        return httpGet("ir-data.somee.com/API/DevicFindByModel?Model=" + model);
    }
    String Device_ByBrandId(int brandId)
    {
        return httpGet("ir-data.somee.com/API/DevicFindByIdBrande?IdBrande=" + String(brandId));
    }

    String Data_getAll() {
        return httpGet("ir-data.somee.com/API/DataAll");
    }
    String Data_ByData(const String& Data)
    {
        return httpGet("ir-data.somee.com/API/DataFindByData?Data=" + Data);
    }
    String Data_ByIdDevice(int deviceId)
    {
        return httpGet("ir-data.somee.com/API/DataFindByIdDevice?id=" + String(deviceId));
    }
    String Data_ByNameKey(const String& nameKey)
    {
        return httpGet("ir-data.somee.com/API/DataFindByNameKey?NameKey=" + nameKey);
    }
    String Data_ById(int dataId)
    {
        return httpGet("ir-data.somee.com/API/DataFindById?id=" + String(dataId));
    }





private:
    String httpGet(const String& url)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            HTTPClient http;
            http.begin(url);
            int httpResponseCode = http.GET();

            String payload = "{}";
            if (httpResponseCode > 0)
            {
                payload = http.getString();
                Serial.print("geted http");
            }
            else
            {
                Serial.print("Error on HTTP request: ");
                Serial.println(httpResponseCode);
            }
            http.end();
            return payload;
        }
        return "{}";
    }
};

class Brand
{
public:
    int ID;
    String BrandName;

    Brand* getAll()
    {
        String json = api.Brand_getAll();
        return Json2BrandArray(json);
    }
    Brand ById(int id)
    {
        String json = api.Brand_ById(id);
        return Json2Brand(json);
    }
    Brand ByName(String id_name)
    {
        String json = api.Brand_ByName(id_name);
        return Json2Brand(json);
    }
private:
    APIClient api = APIClient();

    Brand Json2Brand(String json)
    {
        Brand itemBrand = Brand();
        StaticJsonDocument<100> doc;

        itemBrand.ID = doc["id"];
        itemBrand.BrandName = doc["brandName"].as<String>();

        return itemBrand;
    }
    Brand* Json2BrandArray(String json)
    {
        StaticJsonDocument<2000> doc;

        JsonArray array = doc.as<JsonArray>();
        Brand arrayBrand[array.size()];
        for (size_t i = 0; i < array.size(); i++)
        {
            JsonObject elem = array[i];
            arrayBrand->ID = elem["id"];
            arrayBrand->BrandName = elem["brandName"].as<String>();
        }
        return arrayBrand;
    }
};
class Device
{
public:
    int Id;
    String Model;
    int IdBrand;

    Device* getAll()
    {
        String json = api.Device_getAll();
        return Json2DeviceArray(json);
    }
    Device ById(int id)
    {
        String json = api.Device_ById(id);
        return Json2Device(json);
    }
    Device ByModel(int id_name)
    {
        String json = api.Device_ById(id_name);
        return Json2Device(json);
    }
    Device* ByBrandId(int id_brand)
    {
        String json = api.Device_ByBrandId(id_brand);
        return Json2DeviceArray(json);
    }
private:
    APIClient api = APIClient();
    Device Json2Device(String json)
    {
        Device itemDevice = Device();
        StaticJsonDocument<100> doc;

        itemDevice.Id = doc["id"];
        itemDevice.IdBrand = doc["idBrand"];
        itemDevice.Model = doc["model"].as<String>();
        return itemDevice;
    }
    Device* Json2DeviceArray(String json)
    {
        StaticJsonDocument<2000> doc;

        JsonArray array = doc.as<JsonArray>();
        Device arrayDevice[array.size()];
        for (size_t i = 0; i < array.size(); i++)
        {
            JsonObject elem = array[i];
            arrayDevice->Id = elem["id"];
            arrayDevice->IdBrand = elem["idBrand"];
            arrayDevice->Model = elem["model"].as<String>();
        }
        return arrayDevice;
    }

};
class DataIr
{
public:
    int Id;
    int IdDevice;
    String Data;
    String NameKey;

    DataIr* DgetAll()
    {
        String json = api.Data_getAll();
        return Json2DataArray(json);
    }
    DataIr* Data_ByIdDevice(int id_device)
    {
        String json = api.Data_ByIdDevice(id_device);
        return Json2DataArray(json);
    }
    DataIr ByData(String data)
    {
        String json = api.Data_ByData(data);
        return Json2Data(json);

    }
    DataIr Data_ByNameKey(String name_key)
    {
        String json = api.Data_ByNameKey(name_key);
        return Json2Data(json);
    }
    DataIr Data_ById(int id)
    {
        String json = api.Data_ById(id);
        return Json2Data(json);
    }
private:
    APIClient api = APIClient();
    DataIr Json2Data(String json)
    {
        DataIr itemData = DataIr();
        StaticJsonDocument<100> doc;

        itemData.Id = doc["id"];
        itemData.IdDevice = doc["idBrand"];
        itemData.NameKey = doc["model"].as<String>();
        itemData.Data = doc["model"].as<String>();
        return itemData;
    }
    DataIr* Json2DataArray(String json)
    {
        StaticJsonDocument<2000> doc;

        JsonArray array = doc.as<JsonArray>();
        DataIr arrayData[array.size()];
        for (size_t i = 0; i < array.size(); i++)
        {
            arrayData->Id = doc["id"];
            arrayData->IdDevice = doc["idBrand"];
            arrayData->NameKey = doc["model"].as<String>();
            arrayData->Data = doc["model"].as<String>();
        }
        return arrayData;

    }

};

#endif

