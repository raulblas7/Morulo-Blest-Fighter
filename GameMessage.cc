
// #include "GameMessage.h"
// #include <memory.h>
// #include <string>

// void GameMessage::to_bin()
// {

//     if (gO)
//     {

//         std::cout << gO->SIZE_SERIALIZABLE << endl;

//         alloc_data(sizeof(GameObject));
//         gO->to_bin();

//         std::cout << gO->size() << endl;
//     }
//     else
//     {
//         alloc_data(1);

//         /*memset(_data, 0, MESSAGE_SIZE);
//         //Serializar los campos type, nick y message en el buffer _data
//         char *tmp = _data;
//         memcpy(tmp, so.c_str(), sizeof(char) * 8);
//         tmp += sizeof(char) * 8;*/
//     }
//     /*  alloc_data(MESSAGE_SIZE);

//     memset(_data, 0, MESSAGE_SIZE);
//     //Serializar los campos type, nick y message en el buffer _data
//     char *tmp = _data;
//     //Copiar tipo a partir de direccion
//     memcpy(tmp, &type, sizeof(uint8_t));
//     tmp += sizeof(uint8_t);
//     //Copiar nick a partir de direccion
//     memcpy(tmp, nick.c_str(), sizeof(char) * 8);
//     tmp += sizeof(char) * 8;
//     //Copiar message a partir de direccion
//     memcpy(tmp, message.c_str(), sizeof(char) * 80);*/
// }

// int GameMessage::from_bin(char *bobj)
// {

//     cout << "alloc\n";
//     alloc_data(MESSAGE_SIZE);
//     cout << "memcpy\n";
//     memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);
//     cout << "memterminao\n";
//     //Reconstruir la clase usando el buffer _data
//     char *tmp = _data;


//     uint8_t type;
//     //Copiar tipo a partir de direccion
//     memcpy((void*)&type, tmp, sizeof(type));
//     cout << type<<"tipo\n";

//     switch ((ObjectType)type)
//     {
//     case ObjectType::PLAYER:
//     {
//         gO = new Player();
//         gO->from_bin(bobj);
//         break;
//     }
//     }
//     /*
//     case ObjectType::BULLET:
//     {
//         ::from_bin(bobj);

//         break;
//     }

//     case ObjectType::PLAYERINFO:
//     {

//         break;
//     }*/

//     return 0;
// }
