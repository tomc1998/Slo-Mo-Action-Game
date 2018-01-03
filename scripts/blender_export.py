import bpy
import os
import json
import re

def main():

    #Get the filename of the current blend
    file_name = bpy.path.basename(bpy.context.blend_data.filepath)
    
    #Find the "." and return the filename up to and including the dot
    file_name = "".join(re.findall(".*\.", file_name))
    
    #Remove the dot
    file_name = file_name[:-1]
    print(file_name)
    
    file_name += ".json"
    
    dir = input("Please enter the directory you wish to export to: ")
    f = open(dir + file_name, "w+")

    
    ix_dict = {0: "posx",
               1: "posy",
               2: "scale",
               3: "rotation"}
    
    keyframes_list = []
    anim_length = 0
    #Loop through each action
    for action in bpy.data.actions:
        keyframes = [[], [], [], []]
        for fc in action.fcurves:
            for kf in fc.keyframe_points:
                #posx and posy
                if fc.data_path == "location":
                    #posx
                    if fc.array_index == 0:
                        #Make sure we are not entering a repeat value
                        if len(keyframes[0]) == 0 or keyframes[0][-1][1] != float(kf.co[1]):
                            keyframes[0].append([int(kf.co[0]) * 10, float(kf.co[1]), kf.interpolation])
                    #posy
                    if fc.array_index == 1:
                        if len(keyframes[1]) == 0 or keyframes[1][-1][1] != float(kf.co[1]):
                            keyframes[1].append([int(kf.co[0]) * 10, float(kf.co[1]), kf.interpolation])
                #scale
                if fc.data_path == "scale":
                    if fc.array_index == 0:
                        if len(keyframes[2]) == 0 or keyframes[2][-1][1] != float(kf.co[1]):
                            keyframes[2].append([int(kf.co[0]) * 10, float(kf.co[1]), kf.interpolation])
                #rotation
                if fc.data_path == "rotation_euler":
                    if fc.array_index == 2:
                        if len(keyframes[3]) == 0 or keyframes[3][-1][1] != float(kf.co[1]):
                            keyframes[3].append([int(kf.co[0]) * 10, float(kf.co[1]), kf.interpolation])
                #update the animation length
                if int(kf.co[0]) * 10 > anim_length:
                    anim_length = int(kf.co[0]) * 10
        keyframes_list.append(keyframes)
    print(keyframes_list)

    #Make sure the last keyframe in any keyframe list has its timestamp as the animation length
    for ix, keyframes in enumerate(keyframes_list):
        for ix2, key_types in enumerate(keyframes):
        
            if len(key_types) > 0 and key_types[-1][0] != anim_length:
                keyframes_list[ix][ix2].append([int(anim_length), key_types[-1][1], key_types[-1][2]])

    
    for ix, keyframes in  enumerate(keyframes_list):
        for ix2, key_types in  enumerate(keyframes):
            vals = [key[1] for key in key_types]
            if all([item == vals[0] for item in vals]) and len(vals) > 2:
                keyframes_list[ix][ix2] = []

    
    data = {}
    for part_id, keyframes in enumerate(keyframes_list):
        data[int(part_id)] = None
        d = {}
        for i, key_type in enumerate(keyframes):
            d[ix_dict[i]] = []
            for key in key_type:
                d[ix_dict[i]].append({"timestamp": int(key[0]), "value": float(key[1]), "interpolation": key[2]})
        data[part_id] = d
#    data["length"] = int(anim_length)
    json.dump(data, f)
    print(json.dumps(data, indent=2))
    
if __name__ == "__main__":
    main()
